using System;
using System.Collections.Generic;
using System.Linq;

class Tokenizer
{
    public enum TokenTypes { Space, Text, Variable, Redir, Pipe };
    class Token
    {
        public string content;
        public TokenTypes tokenType;
        public bool inQuotes; // Only Important For Variables And Text Tokens
        public Token(string _content, TokenTypes _tokenType, bool _inQuotes)
        {
            content = _content;
            tokenType = _tokenType;
            inQuotes = _inQuotes;
        }
    }
    class RefinedToken
    {
        public TokenTypes tokenType;
        public TextNode textNode;
        public RedirNode redirNode;
        public PipeNode pipeNode;
        public RefinedToken(TokenTypes _tokenType, object _node)
        {
            tokenType = _tokenType;
            if (_tokenType == TokenTypes.Text)
                textNode = _node as TextNode;
            else if (_tokenType == TokenTypes.Redir)
                redirNode = _node as RedirNode;
            else if (_tokenType == TokenTypes.Pipe)
                pipeNode = _node as PipeNode;
        }
    }
    class TextNode
    {
        public string original;
        public LinkedList<string> expanded;
        public bool inQuotes; // Important For Heredoc Delimiters And Ambiguous Error
        public TextNode(string _original, LinkedList<string> _expanded, bool _inQuotes)
        {
            original = _original;
            expanded = _expanded;
            inQuotes = _inQuotes;
        }
    }
    class RedirNode
    {
        public TextNode data;
        public enum RedirTypes { Infile, Outfile, Append, Heredoc };
        public RedirTypes redirType;
        public RedirNode(TextNode _data, RedirTypes _redirType)
        {
            data = _data;
            redirType = _redirType;
        }
    }
    class PipeNode
    {
        public PipeNode()
        {

        }
    }
    class Command
    {
        public LinkedList<TextNode> args;
        public LinkedList<RedirNode> redirs;
    }
    static readonly string dashLine = "-------------------------------------------------";
    public static void ParseCommand(string _cmd)
    {
        Console.WriteLine(dashLine);
        Console.WriteLine($"Given Command: {_cmd}");
        Console.WriteLine(dashLine);
        LinkedList<Token> rawTokens = SplitTokens(_cmd);
        Console.WriteLine(dashLine);
        Console.WriteLine($"Split Tokens: {rawTokens.Count}");
        foreach (Token t in rawTokens)
            Console.WriteLine($"{t.content} {new string[5] { "(Space)", "(Text)", "(Variable)", "(Redirection)", "(Pipe)" }[(int)t.tokenType]} {(t.inQuotes ? "(In Quotes)" : "")}");
        Console.WriteLine(dashLine);
        SyntaxCheck(rawTokens);
        Console.WriteLine(dashLine);
        Console.WriteLine($"Refined Tokens:");
        foreach (RefinedToken node in RefineTokens(rawTokens))
        {
            if (node.tokenType == TokenTypes.Text)
            {
                Console.WriteLine($"Text (Original): {node.textNode.original} {(node.textNode.inQuotes ? "(In Quotes)" : "")}");
                Console.WriteLine($"Expansion Text Nodes: {node.textNode.expanded.Count}");
                foreach (string s in node.textNode.expanded)
                    Console.WriteLine($"-\t`{s}`");
            }
            else if (node.tokenType == TokenTypes.Redir)
            {
                Console.WriteLine($"Redirection ({node.redirNode.redirType})");
            }
            else if (node.tokenType == TokenTypes.Pipe)
            {
                Console.WriteLine("Pipe");
            }
        }
        string expandedFull = string.Empty;
        foreach (RefinedToken node in RefineTokens(rawTokens))
        {
            if (node.tokenType == TokenTypes.Text)
                foreach (string s in node.textNode.expanded)
                    expandedFull += $"`{s}` ";
        }
        Console.WriteLine($"Full Expansion: {expandedFull}");
        Console.WriteLine(dashLine);
    }
    enum QuoteStatus { None, Single, Double };
    static LinkedList<Token> SplitTokens(string _cmd)
    {
        int i;
        int start;
        char lastQuote = '\0';
        LinkedList<Token> tokens;

        i = 0;
        tokens = new LinkedList<Token>();
        while (i < _cmd.Length)
        {
            start = i;
            while (i < _cmd.Length && IsSpaceChar(_cmd[i]) && lastQuote == '\0')
                i++;
            if (i > start)
                tokens.AddLast(new Token(string.Empty, TokenTypes.Space, lastQuote != '\0'));
            start = i;
            while (i < _cmd.Length && !(lastQuote == '\'' ? _cmd[i] == '\'' : lastQuote == '"' ? "\"$".Contains(_cmd[i]) : IsControlChar(_cmd[i])))
                i++;
            if (i > start || lastQuote != '\0')
                tokens.AddLast(new Token(_cmd.Substring(start, i - start), TokenTypes.Text, lastQuote != '\0'));
            if (i < _cmd.Length && "$<>|\"'".Contains(_cmd[i]))
            {
                if ("\"'".Contains(_cmd[i]))
                {
                    if (lastQuote == _cmd[i])
                        lastQuote = '\0';
                    else if (lastQuote == '\0')
                        lastQuote = _cmd[i];
                    i++;
                }
                else if (_cmd[i] == '$' && lastQuote != '\'')
                {
                    start = ++i;
                    while (i < _cmd.Length && (char.IsLetterOrDigit(_cmd[i]) || _cmd[i] == '_' || (_cmd[i] == '?' && start == i)))
                        i++;
                    if (i == start)
                        throw new Exception("Error: Variable With No Name Detected!");
                    tokens.AddLast(new Token(_cmd.Substring(start, i - start), TokenTypes.Variable, lastQuote != '\0'));
                }
                else if (lastQuote == '\0')
                {
                    start = i;
                    if (i + 1 < _cmd.Length && "<>".Contains(_cmd[i]) && _cmd[i] == _cmd[i + 1])
                        i++;
                    tokens.AddLast(new Token(_cmd.Substring(start, ++i - start), _cmd[start] == '|' ? TokenTypes.Pipe : TokenTypes.Redir, lastQuote != '\0'));
                }
            }
        }
        if (lastQuote != '\0')
            throw new Exception("Error: Open Quotes Detected!");
        return tokens;
    }
    static void SyntaxCheck(LinkedList<Token> _tokenList)
    {
        LinkedListNode<Token> cursor = _tokenList.First;
        LinkedListNode<Token> prevToken = null;
        while (cursor != null)
        {
            if (cursor.Value.tokenType != TokenTypes.Space)
            {
                if (cursor.Value.tokenType == TokenTypes.Pipe)
                {
                    if (prevToken == null)
                        throw new Exception("Syntax Error: Pipe At Start Of Command!");
                    else if (prevToken.Value.tokenType == TokenTypes.Pipe)
                        throw new Exception("Syntax Error: Empty Command Between Pipes!");
                    else if (prevToken.Value.tokenType == TokenTypes.Redir)
                        throw new Exception("Syntax Error: Incomplete Redirection!");
                }
                else if (cursor.Value.tokenType == TokenTypes.Redir)
                {
                    if (prevToken.Value.tokenType == TokenTypes.Redir)
                        throw new Exception("Syntax Error: Incomplete Redirection!");
                }
                prevToken = cursor;
            }
            cursor = cursor.Next;
        }
        if (prevToken.Value.tokenType == TokenTypes.Pipe)
            throw new Exception("Syntax Error: Pipe At End Of Command!");
        else if (prevToken.Value.tokenType == TokenTypes.Redir)
            throw new Exception("Syntax Error: Incomplete Redirection At End Of Command!");
    }
    static LinkedList<RefinedToken> RefineTokens(LinkedList<Token> _tokenList)
    {
        LinkedList<RefinedToken> refinedTokens = new LinkedList<RefinedToken>();
        string original = string.Empty;
        LinkedList<string> expanded = new LinkedList<string>();
        bool inQuotes = false;
        bool addNew = false;
        foreach (Token token in _tokenList)
        {
            if (token.tokenType != TokenTypes.Text && token.tokenType != TokenTypes.Variable)
            {
                if (!string.IsNullOrEmpty(original) || inQuotes)
                {
                    refinedTokens.AddLast(new RefinedToken(TokenTypes.Text, new TextNode(original, expanded, inQuotes)));
                    original = string.Empty;
                    expanded = new LinkedList<string>();
                    inQuotes = false;
                }
                if (token.tokenType == TokenTypes.Redir)
                {
                    RedirNode.RedirTypes redirType = RedirNode.RedirTypes.Infile;
                    if (token.content == ">")
                        redirType = RedirNode.RedirTypes.Outfile;
                    else if (token.content == "<<")
                        redirType = RedirNode.RedirTypes.Heredoc;
                    else if (token.content == ">>")
                        redirType = RedirNode.RedirTypes.Append;
                    refinedTokens.AddLast(new RefinedToken(TokenTypes.Redir, new RedirNode(null, redirType)));
                }
                else if (token.tokenType == TokenTypes.Pipe)
                    refinedTokens.AddLast(new RefinedToken(TokenTypes.Pipe, new PipeNode()));
            }
            else
            {
                if (token.tokenType == TokenTypes.Variable)
                {
                    original += '$' + token.content;
                    string expansion = GetEnv(token.content);
                    if (expansion != null)
                    {
                        if (token.inQuotes)
                            expanded.Last.Value += GetEnv(token.content);
                        else
                        {
                            string[] splitNodes = expansion.Split(new char[] { ' ', '\t', '\n' }, StringSplitOptions.RemoveEmptyEntries);
                            for (int i = 0; i < splitNodes.Length; i++)
                            {
                                if (i == 0 && (expanded.Count == 0 || !IsSpaceChar(expansion[0])))
                                {
                                    if (expanded.Count == 0)
                                        expanded.AddLast(string.Empty);
                                    expanded.Last.Value += splitNodes[i];
                                }
                                else
                                    expanded.AddLast(splitNodes[i]);
                            }
                            addNew = expansion.Length > 0 && IsSpaceChar(expansion[expansion.Length - 1]);
                        }
                    }
                }
                else
                {
                    original += token.content;
                    if (addNew)
                    {
                        addNew = false;
                        expanded.AddLast(token.content);
                    }
                    else
                    {
                        if (expanded.Count == 0)
                            expanded.AddLast(string.Empty);
                        expanded.Last.Value += token.content;
                    }
                }
                inQuotes = inQuotes || token.inQuotes;
            }
        }
        if (!string.IsNullOrEmpty(original))
            refinedTokens.AddLast(new RefinedToken(TokenTypes.Text, new TextNode(original, expanded, inQuotes)));
        return refinedTokens;
    }
    static bool IsSpaceChar(char c) { return " \t\n".Contains(c); }
    static bool IsControlChar(char c) { return IsSpaceChar(c) || "$<>|\"'".Contains(c); }
    // Mock-Up Of getenv() Function
    static string GetEnv(string _var)
    {
        switch (_var)
        {
            //case "a": return "    1    2    ";
            //case "b": return "    3    4    ";
            case "a": return "1";
            case "b": return "";
            case "n": return "";
            case "no": return null;
            default: return $"<Value_Of_${_var}>";
        }
    }
    static LinkedList<Command> BuildCommands(LinkedList<Token> _tokens)
    {
        LinkedList<Command> commands = new LinkedList<Command>();
        return commands;
    }
}