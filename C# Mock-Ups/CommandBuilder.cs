using System.Collections.Generic;
using static Refiner;

class CommandBuilder
{
    public class Command
    {
        public LinkedList<TextToken> args;
        public LinkedList<RedirToken> redirs;
        public Command()
        {
            args = new LinkedList<TextToken>();
            redirs = new LinkedList<RedirToken>();
        }
    }
    public static LinkedList<Command> BuildCommands(LinkedList<RefinedToken> _tokens)
    {
        LinkedList<Command> commands = new LinkedList<Command>();
        Command command = null;
        LinkedListNode<RefinedToken> cursor = _tokens.First;
        LinkedListNode<RefinedToken> prev = null;
        while (cursor != null)
        {
            if (cursor.Value.tokenType == RefinedTokenTypes.Pipe)
            {
                commands.AddLast(command);
                command = null;
            }
            else
            {
                if (command == null)
                    command = new Command();
                if (cursor.Value.tokenType == RefinedTokenTypes.Text)
                {
                    if (prev != null && prev.Value.tokenType == RefinedTokenTypes.Redir)
                        prev.Value.redirToken.text = cursor.Value.textToken;
                    else
                        command.args.AddLast(cursor.Value.textToken);
                }
                else
                    command.redirs.AddLast(cursor.Value.redirToken);
            }
            prev = cursor;
            cursor = cursor.Next;
        }
        if (command != null)
            commands.AddLast(command);
        return commands;
    }
}