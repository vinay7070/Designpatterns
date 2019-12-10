#  Vinay Daniel Washington
#  U00882938
#  PROJECT 00
#  Professor: Erik Buck 




#list that stores the arguments required for undo and redo operations such as the character being deleted in delete_end
argumentlist_undo=[]
argumentlist_redo=[]

#string being used for all the operations declared globally
a="command pattern"


#base class that has methods to execute and to fetch the opposite command of the current command
class Command:
    def execute(self, argument):
        pass

    def oppositeCommand(self):
        pass

class Invoker:
    def __init__(self):
        self.redoStack = []
        self.undoStack = []
        self.currentStack=self.undoStack


    def invoke(self, command, argument):
        command.execute(argument)
        #pushing the oppossite command of the current command into the stack
        self.currentStack.append(command.oppositeCommand())

    def undo(self):
        #removing the command from the undoStack as it is gonna be performed
        c=self.undoStack.pop()
        #changing currentStack to redoStack
        self.currentStack=self.redoStack
        #calling the undo operation with the last entry to the argumentlist
        self.invoke(c, argumentlist_undo.pop())
        if not (len(argumentlist_undo) == 1):
            argumentlist_redo.append(argumentlist_undo.pop())
        else:
            argumentlist_redo.append(argumentlist_undo[-1])
        #changing currentStack back to undoStack
        self.currentStack = self.undoStack

    def redo(self):
        #removing the command from the redoStack
        c=self.redoStack.pop()
        #changing currentStack to undoStack
        self.currentStack = self.undoStack
        #calling the redo operation with the last entry to the argumentlist
        self.invoke(c, argumentlist_redo.pop())
        #changing currentStack back to redoStack
        self.currentStack = self.redoStack

#class for the command that performs appending a character to the end
class Appending(Command):

    def execute(self, argument):
        global a
        argumentlist_undo.append(argument)
        a = a + argument
        print ("String after appending_last : "+a)


    def oppositeCommand(self):
        return Deleting_last()


#class for the command that performs deleting the starting character
class Deleting_start(Command):
    def execute(self, argument):
        global a
        argumentlist_undo.append(a[0])
        a= a[1:]
        print ("String deleting_start : "+a)

    def oppositeCommand(self):
        return Appending_start()


#class for the command that performs appending the starting character
class Appending_start(Command):
    def execute(self, argument):
        global a
        a = argument + a
        print ("String after appending_start :"+a)
        #print (a, argumentlist_undo[-1])

    def oppositeCommand(self):
        return Deleting_start()


 #class for the command that performs deleting the ending character
class Deleting_last(Command):
    def execute(self, argument):
        global a
        argumentlist_undo.append(a[-1])
        a = a[:-1]
        print ("String after deleting_last :"+a)

    def oppositeCommand(self):
        return Appending()


#class for the command that performs uppercasing of the starting character
class Capitalizing(Command):

    def execute(self, argument):
        global a
        a = a[0].capitalize() + a[1:]
        argumentlist_undo.append("something")
        print ("String after capitalizing_start : "+a)

    def oppositeCommand(self):
        return Lowercasing()


#class for the command that performs lowercasing of the starting character
class Lowercasing(Command):
    def execute(self, argument):
        global a
        a = a[0].lower() + a[1:]
        argumentlist_undo.append("something")
        print ("String after lowercasing_start : "+a)

    def oppositeCommand(self):
        return Capitalizing()


#class for the command that performs titlecasing
class Titlecasing(Command):
    def execute(self, argument):
        global a
        argumentlist_undo.append(a)
        a=a.title()
        print ("String after Titlecasing : "+a)

    def oppositeCommand(self):
        return UndoTitlecasing()


#class for the command that reverts titlecasing
class UndoTitlecasing(Command):
    def execute(self, argument):
        global a
        a = argument
        argumentlist_undo.append(a)
        print ("String after undoing Titlecase : "+a)

    def oppositeCommand(self):
        return UndoTitlecasing()




def main():
    invoker = Invoker()
    print ("String used is \"command pattern\"")
    appendcommand = Appending()
    delete_startcommand = Deleting_start()
    delete_endcommand = Deleting_last()
    capitalizecommand = Capitalizing()
    lowercasecommand = Lowercasing()
    titlecasecommand = Titlecasing()
    invoker.invoke(appendcommand, "v")
    invoker.invoke(appendcommand, "x")
    invoker.invoke(delete_startcommand, None)
    invoker.invoke(capitalizecommand, None)
    invoker.invoke(delete_endcommand, None)
    invoker.invoke(titlecasecommand, None)
    print ("\n\n Undo operations")
    invoker.undo()
    invoker.undo()
    invoker.undo()
    invoker.undo()
    invoker.undo()
    invoker.undo()
    print ("\n\n Redo Operations")
    invoker.redo()
    invoker.redo()
    invoker.redo()
    invoker.redo()
    invoker.redo()




if __name__== '__main__':

    main()
