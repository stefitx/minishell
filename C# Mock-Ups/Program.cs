using System;
using System.Collections.Generic;

class Program
{
    static void Main(string[] args)
    {
        //string cmd = "ls -l >> file1 | wc < \"$a\"$b/file3 '' \"a\"'b' $n$a$b > file2";
        string cmd = "'a' \"$a\" $b";
        //string cmd = "echo $a$b\"\"";
        //string cmd = "$no";
        LinkedList<Tokenizer.Command> commands = Tokenizer.ParseCommand(cmd);
        Console.ReadKey();
    }
}