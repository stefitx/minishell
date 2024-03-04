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
        public TextNode textNode;
        public RedirNode redirNode;
        public PipeNode pipeNode;
        public RefinedToken(RefinedTokenTypes _tokenType, object _node)
        {
            tokenType = _tokenType;
            if (_tokenType == RefinedTokenTypes.Text)
                textNode = _node as TextNode;
            else if (_tokenType == RefinedTokenTypes.Redir)
                redirNode = _node as RedirNode;
            else if (_tokenType == RefinedTokenTypes.Pipe)
                pipeNode = _node as PipeNode;
        }
    }
    public class TextNode
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
    public class RedirNode
    {
        public TextNode text;
        public enum RedirTypes { Infile, Outfile, Append, Heredoc };
        public RedirTypes redirType;
        public RedirNode(TextNode _data, RedirTypes _redirType)
        {
            text = _data;
            redirType = _redirType;
        }
    }
    public class PipeNode
    {
        public PipeNode()
        {

        }
    }
    public class Command
    {
        public LinkedList<TextNode> args;
        public LinkedList<RedirNode> redirs;
    }
    static bool IsSpaceChar(char c) { return " \t\n".Contains(c); }
    public static LinkedList<RefinedToken> RefineTokens(LinkedList<Token> _tokenList)
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
                    refinedTokens.AddLast(new RefinedToken(RefinedTokenTypes.Text, new TextNode(original, expanded, inQuotes)));
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
                    refinedTokens.AddLast(new RefinedToken(RefinedTokenTypes.Redir, new RedirNode(null, redirType)));
                }
                else if (token.tokenType == TokenTypes.Pipe)
                    refinedTokens.AddLast(new RefinedToken(RefinedTokenTypes.Pipe, new PipeNode()));
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
            refinedTokens.AddLast(new RefinedToken(RefinedTokenTypes.Text, new TextNode(original, expanded, inQuotes)));
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
    static LinkedList<Command> BuildCommands(LinkedList<RefinedToken> _tokens)
    {
        LinkedList<Command> commands = new LinkedList<Command>();
        return commands;
    }
}
