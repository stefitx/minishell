using System;
using System.Collections.Generic;
using System.Linq;
using static Tokenizer;

class Refiner
{
    public enum RefinedTokenTypes { Text, Redir, Pipe };
    public class RefinedToken
    {
        public RefinedTokenTypes tokenType;
        public TextToken textToken;
        public RedirToken redirToken;
        public PipeToken pipeNode;
        public RefinedToken(RefinedTokenTypes _tokenType, object _node)
        {
            tokenType = _tokenType;
            if (_tokenType == RefinedTokenTypes.Text)
                textToken = _node as TextToken;
            else if (_tokenType == RefinedTokenTypes.Redir)
                redirToken = _node as RedirToken;
            else if (_tokenType == RefinedTokenTypes.Pipe)
                pipeNode = _node as PipeToken;
        }
    }
    public class TextToken
    {
        public string original;
        public LinkedList<string> expanded;
        public bool inQuotes; // Important For Heredoc Delimiters And Ambiguous Error
        public TextToken(string _original, LinkedList<string> _expanded, bool _inQuotes)
        {
            original = _original;
            expanded = _expanded;
            inQuotes = _inQuotes;
        }
    }
    public class RedirToken
    {
        public TextToken text;
        public enum RedirTypes { Infile, Outfile, Append, Heredoc };
        public RedirTypes redirType;
        public RedirToken(TextToken _data, RedirTypes _redirType)
        {
            text = _data;
            redirType = _redirType;
        }
    }
    public class PipeToken
    {
        // Not Actually Used Yet, Just Here As A Mock-Up
        public int fd_in;
        public int fd_out;
        public PipeToken()
        {

        }
    }
    static bool IsSpaceChar(char c) { return " \t\n".Contains(c); }
    public static LinkedList<RefinedToken> RefineTokens(LinkedList<Token> _tokenList)
    {
        LinkedList<RefinedToken> refinedTokens = new LinkedList<RefinedToken>();
        string original = null;
        LinkedList<string> expanded = new LinkedList<string>();
        bool inQuotes = false;
        bool addNew = false;
        foreach (Token token in _tokenList)
        {
            if (token.tokenType != TokenTypes.Text && token.tokenType != TokenTypes.Variable)
            {
                if (!string.IsNullOrEmpty(original) || inQuotes)
                {
                    refinedTokens.AddLast(new RefinedToken(RefinedTokenTypes.Text, new TextToken(original, expanded, inQuotes)));
                    original = null;
                    expanded = new LinkedList<string>();
                    inQuotes = false;
                }
                if (token.tokenType == TokenTypes.Redir)
                {
                    RedirToken.RedirTypes redirType = RedirToken.RedirTypes.Infile;
                    if (token.content == ">")
                        redirType = RedirToken.RedirTypes.Outfile;
                    else if (token.content == "<<")
                        redirType = RedirToken.RedirTypes.Heredoc;
                    else if (token.content == ">>")
                        redirType = RedirToken.RedirTypes.Append;
                    refinedTokens.AddLast(new RefinedToken(RefinedTokenTypes.Redir, new RedirToken(null, redirType)));
                }
                else if (token.tokenType == TokenTypes.Pipe)
                    refinedTokens.AddLast(new RefinedToken(RefinedTokenTypes.Pipe, new PipeToken()));
            }
            else
            {
                if (token.tokenType == TokenTypes.Variable)
                {
                    if (original == null)
                        original = string.Empty;
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
                    if (original == null)
                        original = string.Empty;
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
        if (original != null)
            refinedTokens.AddLast(new RefinedToken(RefinedTokenTypes.Text, new TextToken(original, expanded, inQuotes)));
        return refinedTokens;
    }
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
}
