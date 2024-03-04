using System;
using System.Collections.Generic;
using static Tokenizer;
using static Refiner;

class Program
{
    static void Main(string[] args)
    {
        string cmd = "ls -l >> file1 | wc < \"$a\"$b/file3 '' \"a\"'b' $n$a$b > file2";
        //string cmd = "'a' \"$a\" $b";
        //string cmd = "\"$n\"$HOME";
        //string cmd = "echo $a$b\"\"";
        //string cmd = "$no";
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
            Console.WriteLine($"{t.content} {new string[5] { "(Space)", "(Text)", "(Variable)", "(Redirection)", "(Pipe)" }[(int)t.tokenType]} {(t.inQuotes ? "(In Quotes)" : "")}");
        Console.WriteLine(dashLine);
        Tokenizer.SyntaxCheck(rawTokens);
        Console.WriteLine(dashLine);
        Console.WriteLine($"Refined Tokens:");
        foreach (RefinedToken node in RefineTokens(rawTokens))
        {
            if (node.tokenType == RefinedTokenTypes.Text)
            {
                Console.WriteLine($"Text (Original): {node.textNode.original} {(node.textNode.inQuotes ? "(In Quotes)" : "")}");
                Console.WriteLine($"Expansion Text Nodes: {node.textNode.expanded.Count}");
                foreach (string s in node.textNode.expanded)
                    Console.WriteLine($"-\t`{s}`");
            }
            else if (node.tokenType == RefinedTokenTypes.Redir)
                Console.WriteLine($"Redirection ({new string[4] { "<", ">", ">>", "<<" }[(int)node.redirNode.redirType]}) ({node.redirNode.redirType})");
            else if (node.tokenType == RefinedTokenTypes.Pipe)
                Console.WriteLine("Pipe (|)");
        }
        string expandedFull = string.Empty;
        foreach (RefinedToken node in RefineTokens(rawTokens))
        {
            if (node.tokenType == RefinedTokenTypes.Text)
                foreach (string s in node.textNode.expanded)
                    expandedFull += $"`{s}` ";
        }
        Console.WriteLine($"Full Expansion: {expandedFull}");
        Console.WriteLine(dashLine);
    }
}