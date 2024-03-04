using System;
using System.Collections.Generic;
using System.Linq;

static class Tokenizer
{
    public enum TokenTypes { Space, Text, Variable, Redir, Pipe };
    enum QuoteStatus { None, Single, Double };
    public class Token
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
    static bool IsSpaceChar(char c) { return " \t\n".Contains(c); }
    static bool IsControlChar(char c) { return IsSpaceChar(c) || "$<>|\"'".Contains(c); }
    public static LinkedList<Token> SplitTokens(string _cmd)
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
    public static void SyntaxCheck(LinkedList<Token> _tokenList)
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
    
}