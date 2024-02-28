using System;
using System.Collections.Generic;
using System.Linq;

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
        public string expanded;
        public bool inQuotes; // Important For Heredoc Delimiters And Ambiguous Error
        public TextNode(string _original, string _expanded, bool _inQuotes)
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
            Console.WriteLine($"{node.expanded} (Original: {node.original}) {(node.inQuotes ? "(In Quotes)" : "")}");
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
            while (i < _cmd.Length && _cmd[i] == ' ' && lastQuote == '\0')
                i++;
            if (i > start)
                tokens.AddLast(new Token(string.Empty, Token.TokenType.Space, lastQuote != '\0'));
            start = i;
            while (i < _cmd.Length && !(lastQuote == '\'' ? "'" : lastQuote == '"' ? "$\"" : " $<>|\"'").Contains(_cmd[i]))
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
        string expanded = string.Empty;
        bool inQuotes = false;
        foreach (Token token in _tokenList)
        {
            if (token.tokenType == Token.TokenType.Space || token.tokenType == Token.TokenType.Special)
            {
                if (!string.IsNullOrEmpty(original))
                {
                    textNodes.AddLast(new TextNode(original, expanded, inQuotes));
                    original = string.Empty;
                    expanded = string.Empty;
                    inQuotes = false;
                }
            }
            else
            {
                if (token.tokenType == Token.TokenType.Variable)
                {
                    original += '$' + token.content;
                    expanded += $"<Value_Of_${token.content}>";
                }
                else
                {
                    original += token.content;
                    expanded += token.content;
                }
                inQuotes = inQuotes || token.inQuotes;
            }
        }
        if (!string.IsNullOrEmpty(original))
            textNodes.AddLast(new TextNode(original, expanded, inQuotes));
        return textNodes;
    }
    //static LinkedList<Command> BuildCommands(LinkedList<Token> _tokens)
    //{
    //    LinkedList<Command> commands = new LinkedList<Command>();
    //    return commands;
    //}
}