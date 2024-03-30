using System;
using System.Collections.Generic;
using static Tokenizer;
using static Refiner;
using static CommandBuilder;

class Program
{
    static void Main(string[] args)
    {
        string cmd = "ls -l >> file1 | wc < \"$a\"$b/file3 '' \"a\"'b' $n$a$b > file2 |''\"\"";
        //string cmd = "'a' \"$a\" $b";
        //string cmd = "\"$n\"$HOME";
        //string cmd = "echo $a$b\"\"";
        //string cmd = "$no";
        //string cmd = "         ''   ";
        //string cmd = "echo -n $HOME | wc -l >> out";
        //string cmd = "  \"$a\"   ";
        ParseCommand(cmd);
        Console.ReadKey();
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
            Console.WriteLine($"{t.content} {new string[6] { "(Space)", "(Text)", "(Variable)", "(Quote)", "(Redirection)", "(Pipe)" }[(int)t.tokenType]} (Quote Status: {t.quoteStatus})");
        Console.WriteLine(dashLine);
        SyntaxCheck(rawTokens);
        LinkedList<RefinedToken> refinedTokens = RefineTokens(rawTokens);
        Console.WriteLine(dashLine);
        Console.WriteLine($"Refined Tokens:");
        foreach (RefinedToken t in refinedTokens)
        {
            if (t.tokenType == RefinedTokenTypes.Text)
            {
                Console.WriteLine($"Text (Original): {t.textToken.original} {(t.textToken.inQuotes ? "(In Quotes)" : "")}");
                Console.WriteLine($"Text (Original Quoted): {t.textToken.originalQuoted} {(t.textToken.inQuotes ? "(In Quotes)" : "")}");
                Console.WriteLine($"Expansion Text Nodes: {t.textToken.expanded.Count}");
                foreach (string s in t.textToken.expanded)
                    Console.WriteLine($"-\t`{s}`");
            }
            else if (t.tokenType == RefinedTokenTypes.Redir)
                Console.WriteLine($"Redirection ({new string[4] { "<", ">", ">>", "<<" }[(int)t.redirToken.redirType]}) ({t.redirToken.redirType})");
            else if (t.tokenType == RefinedTokenTypes.Pipe)
                Console.WriteLine("Pipe (|)");
        }
        //string expandedFull = string.Empty;
        //foreach (RefinedToken t in refinedTokens)
        //{
        //    if (t.tokenType == RefinedTokenTypes.Text)
        //        foreach (string s in t.textToken.expanded)
        //            expandedFull += $"`{s}` ";
        //}
        //Console.WriteLine($"Full Expansion: {expandedFull}");
        Console.WriteLine(dashLine);
        LinkedList<Command> commands = BuildCommands(refinedTokens);
        Console.WriteLine(dashLine);
        Console.WriteLine($"Commands: {commands.Count}");
        foreach(Command c in commands)
        {
            Console.WriteLine();
            Console.WriteLine($"Arguments: {c.args.Count}");
            foreach (TextToken t in c.args)
                Console.WriteLine($"-\t`{t.original}`");
            Console.WriteLine($"Redirections: {c.redirs.Count}");
            foreach (RedirToken t in c.redirs)
                Console.WriteLine($"-\t{new string[4] { "<", ">", ">>", "<<" }[(int)t.redirType]} {t.text.original}");
        }
        Console.WriteLine(dashLine);
    }
}