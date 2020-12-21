Overall, this assignment wasn't as difficult as I expected especially considering
all of the things that I've heard from others about it. In fact, I actually really
enjoyed working through this assignment and figuring out how to implement each
operation. Working with all of the system calls I found super interesting and gives
great insight into how a shell actually works.

When it comes to the code itself the first decision I made was to use execvp instead
of execlp. This decision was easily made as execvp in my opinion results in neater
code and is infinitely scalable. To manage this I first implemented execvp  in a test program
to get a good idea of how the call actually functions. When it came to dealing with the
double pointers I also felt like it was fairly straightforward because you are
essentially just working with an array of strings.

Once I finished figuring out how I would fork and create child processes I needed
to figure out how I would take input from the user. I did this using a do while
loop which will run until the user types 'exit'. This allows for shell-like behavior.
I then use fgets to take a command from the user and once I have the command I need
to parse the command. The command was parsed using strtok, first to get rid of the
trailing newline character, and then split by using the ' ' delimiter. Each token
was then stored into an array of character arrays. Since this shell took arguments
backwards I then needed to reverse the order of the arguements so that it could be
used with the execvp system call. Once I had my list of arguments, I just needed
to scan the list for any special characters such as > < | or & and if one of these
is encountered perform the specific operation associated with the operator. If no special
characters were found then the next condition to check is if the user entered 'fg'
and if so bring the most recent background process to the foreground if one existed.
If none of these conditions are true then the program executes the list of arguments
normally, waits for the child process to finish, and then re-prompts the user for more
input.
