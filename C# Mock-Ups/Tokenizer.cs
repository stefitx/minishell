using System;
using System.Collections.Generic;
using System.Linq;
using System.Xml.Linq;

class Tokenizer
{
    struct Token
    {
        public string content;
        public enum TokenType { Space, Text, Variable, Special };
        public TokenType tokenType;
        public bool inQuotes; // Only Important For Variables And Text Tokens
        public Token(string _content, TokenType _tokenType, bool _inQuotes)
        {
            content = _content;
            tokenType = _tokenType;
            inQuotes = _inQuotes;
        }
    }
    struct TextNode
    {
        public string original;
        public string[] expanded;
        public bool inQuotes; // Important For Heredoc Delimiters And Ambiguous Error
        public TextNode(string _original, string[] _expanded, bool _inQuotes)
        {
            original = _original;
            expanded = _expanded;
            inQuotes = _inQuotes;
        }
    }
    public struct Command
    {
        //LinkedList<string> commandParts;
        //LinkedList<Token> redirectionQueue;
        //Token infile;
        //Token outfile;
    }
    static readonly string dashLine = "-------------------------------------------------";
    public static LinkedList<Command> ParseCommand(string _cmd)
    {
        Console.WriteLine(dashLine);
        Console.WriteLine($"Given Command: {_cmd}");
        Console.WriteLine(dashLine);
        LinkedList<Token> rawTokens = SplitTokens(_cmd);
        Console.WriteLine(dashLine);
        Console.WriteLine($"Split Tokens: {rawTokens.Count}");
        foreach (Token t in rawTokens)
            Console.WriteLine($"{t.content} {new string[4] { "(Space)", "(Text)", "(Variable)", "(Special)" }[(int)t.tokenType]} {(t.inQuotes ? "(In Quotes)" : "")}");
        Console.WriteLine(dashLine);
        Console.WriteLine(dashLine);
        Console.WriteLine($"Joined Text Nodes:");
        foreach (TextNode node in JoinTextNodes(rawTokens))
        {
            Console.WriteLine($"Original: {node.original} {(node.inQuotes ? "(In Quotes)" : "")}");
            Console.WriteLine($"Expansion Text Nodes: {node.expanded.Length}");
            foreach (string s in node.expanded)
                Console.WriteLine($"-\t`{s}`");
        }
        string expandedFull = string.Empty;
        foreach (TextNode node in JoinTextNodes(rawTokens))
        {
            foreach (string s in node.expanded)
                expandedFull += $"`{s}` ";
        }
        Console.WriteLine($"Full Expansion: {expandedFull}");
        Console.WriteLine(dashLine);
        return null;
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
                tokens.AddLast(new Token(string.Empty, Token.TokenType.Space, lastQuote != '\0'));
            start = i;
            while (i < _cmd.Length && !(lastQuote == '\'' ? _cmd[i] == '\'' : lastQuote == '"' ? "\"$".Contains(_cmd[i]) : IsControlChar(_cmd[i])))
                i++;
            if (i > start || lastQuote != '\0')
                tokens.AddLast(new Token(_cmd.Substring(start, i - start), Token.TokenType.Text, lastQuote != '\0'));
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
                    tokens.AddLast(new Token(_cmd.Substring(start, i - start), Token.TokenType.Variable, lastQuote != '\0'));
                }
                else if (lastQuote == '\0')
                {
                    start = i;
                    if (i + 1 < _cmd.Length && "<>".Contains(_cmd[i]) && _cmd[i] == _cmd[i + 1])
                        i++;
                    tokens.AddLast(new Token(_cmd.Substring(start, ++i - start), Token.TokenType.Special, lastQuote != '\0'));
                }
            }
        }
        if (lastQuote != '\0')
            throw new Exception("Error: Open Quotes Detected!");
        return tokens;
    }
    static LinkedList<TextNode> JoinTextNodes(LinkedList<Token> _tokenList)
    {
        LinkedList<TextNode> textNodes = new LinkedList<TextNode>();
        string original = string.Empty;
        LinkedList<string> expanded = new LinkedList<string>();
        bool inQuotes = false;
        bool addNew = false;
        foreach (Token token in _tokenList)
        {
            if (token.tokenType == Token.TokenType.Space || token.tokenType == Token.TokenType.Special)
            {
                if (!string.IsNullOrEmpty(original) || inQuotes)
                {
                    textNodes.AddLast(new TextNode(original, expanded.ToArray(), inQuotes));
                    original = string.Empty;
                    expanded.Clear();
                    inQuotes = false;
                }
            }
            else
            {
                if (token.tokenType == Token.TokenType.Variable)
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
                                if (i == 0 && ((expanded.Last.Value == string.Empty && !inQuotes) || !IsSpaceChar(expansion[0])))
                                {
                                    if (expanded.Count == 0)
                                        expanded.AddLast(string.Empty);
                                    expanded.Last.Value += splitNodes[i];
                                }
                                else
                                    expanded.AddLast(splitNodes[i]);
                            }
                            addNew = IsSpaceChar(expansion[expansion.Length - 1]);
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
            textNodes.AddLast(new TextNode(original, expanded.ToArray(), inQuotes));
        return textNodes;
    }
    static bool IsSpaceChar(char c) { return " \t\n".Contains(c); }
    static bool IsControlChar(char c) { return IsSpaceChar(c) || "$<>|\"'".Contains(c); }
    // Mock-Up Of getenv() Function
    static string GetEnv(string _var)
    {
        switch (_var)
        {
            case "a": return "    1    2    ";
            case "b": return "    3    4    ";
            case "no": return null;
            default: return $"<Value_Of_${_var}>";
        }
    }
    //static LinkedList<Command> BuildCommands(LinkedList<Token> _tokens)
    //{
    //    LinkedList<Command> commands = new LinkedList<Command>();
    //    return commands;
    //}
}