﻿using System;
using System.Collections.Generic;

class Program
{
    static void Main(string[] args)
    {
        string cmd = "ls -l >> file1 | wc < \"$HOME\"$?/file3 \"a\"'b' > file2";
        LinkedList<Tokenizer.Command> commands = Tokenizer.ParseCommand(cmd);
        Console.ReadKey();
    }
}