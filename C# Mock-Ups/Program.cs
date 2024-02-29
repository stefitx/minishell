using System;
using System.Collections.Generic;

class Program
{
    static void Main(string[] args)
    {
        //string cmd = "ls -l >> file1 | wc < \"$a\"$b/file3 \"a\"'b' > file2";
        string cmd = "echo $a$b\"\"";
        LinkedList<Tokenizer.Command> commands = Tokenizer.ParseCommand(cmd);
        Console.ReadKey();
    }
}