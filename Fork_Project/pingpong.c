//Caleb Sannes 
//ID: 5715662
//sanne118

//include depedencies shouldn't be much more than strings.h probably
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/wait.h>


//two gobal variables to indicate when certain signals are recieved

int Flag = 0; //indicates that the child or parent has signaled the other to write in the log
int GraceFail = 0; //indicates that the child or parent has failed for some unexpected reason

void rec_sig(int sig) //handler function for the processes signalling each other to write in the log
{
    Flag = 1;
    return;
}

void rec_exit(int sig) //handler function for the other process failing unexpectedly
{
    GraceFail = 1;
    return;
}



int main(int argc, char **argv) 
{
    int limit;
    int counter =0;

    if(argc != 2) //ensures the correct number of arguments
    {
        printf("Incorrect number of arguments...\n");
        printf("Usage: ./pingpong # (where # is the desired limit)\n");
        return 1;
    }
    else
    {
        limit = atoi(argv[1]); //converst the arugment from a string to a int such that it can be set as limit
    } 
    int parent_pid, child_pid;
    parent_pid = getpid(); //gets the parent pid

    sigset_t *mask; //creates the signal mask set

    int check;

    check = sigemptyset(mask); //ensures the signal mask set is empty 
    if(check == -1) 
    {
        printf("error in creating signal set\n");
        exit(1);
    }

    

    check = sigaddset(mask,SIGUSR1); //adds the SIGUSR1 signal to the set
    if(check == -1) {
        printf("error in adding signal 1 to set\n");
        exit(1);
    }

    check = sigaddset(mask,SIGUSR2); //adds the SIGUSR2 signal to the set
    if(check == -1) { 
        printf("error in adding signal 2 to set\n");
        exit(1);
    }

    check = sigprocmask(SIG_BLOCK,mask,NULL); //adds the signal set to the mask blocking them temporarily 
    if(check == -1) { 
        printf("error in masking signal 2\n");
        exit(1);
    }

    FILE *log = fopen("log.txt","w"); //opens the log file descriptor 
    if(log == NULL) { 
        printf("error in opening file\n");
        exit(1);
    }

    child_pid = fork(); //forks the child process of the parent process
    if(child_pid == -1) {
        printf("error in forking\n");
        exit(1);
    }

    else if(child_pid != 0) //Parent Case
    {
        printf("Parent::parent process executing with LIMIT = %d\n", limit);
        printf("Parent::parent process id = %d\n", parent_pid);
        
        signal(SIGUSR2,rec_sig); //sets up the signal handlers
        signal(SIGCHLD,rec_exit);

        Flag = 1; //sets Flag to 1 so the process will write to the log on the intial pass through the while loop        

        check = sigemptyset(mask); //clears the signal set
        if(check == -1) { 
            printf("error in emptying parent signal set\n");
            exit(1);
        }


        while(counter <= limit) 
        {

            if(Flag == 1) //only triggers on the intial run and after the signal from the child has been sent
            {
                check = fprintf(log,"Parent %d\n", counter);
                if(check < 0) { 
                    printf("error in writing to file as parent\n");
                    exit(1);
                }
                check = fflush(log); //esures the buffer is flushed and data written to the file immediatly 
                if(check != 0) { 
                    printf("error in flushing stream\n");
                    exit(1);
                }

                check = kill(child_pid,SIGUSR1); //sends SIGUSR1 signal to the child
                if(check == -1) { 
                    printf("error in sending signal to child\n");
                    exit(1);
                }

                counter++;
                Flag = 0;
            }
            if(GraceFail == 1)
            {
                return 1;
            }
            sigsuspend(mask); //halts the process to wait for any signal 

        }
        check = wait(NULL); //waits for the child process to terminate
        if(check == -1) { 
            printf("error in waiting for child\n");
            exit(1);
        }
    
    }
    else //child case 
    {
        signal(SIGUSR1,rec_sig); //sets up signal handling for normal signal from parent

        check = prctl(PR_SET_PDEATHSIG, SIGUSR2); //tells the system to send the child a signal if the parent terminates
        if(check == -1) { 
            printf("error in setting up signal to child when parent dies\n");
            exit(1);
        }
        
        signal(SIGUSR2,rec_exit); //signal handler for if the parent terminates 
        
        printf("Child::child process executing with LIMIT = %d\n", limit);
        printf("Child::child process id = %d\n", getpid());

        check = sigemptyset(mask); //clears the signal set
        if(check == -1) { 
            printf("error in emptying child signal set\n");
            exit(1);
        }

        while(counter <= limit) 
        {
            sigsuspend(mask); //halts the processes and waits for any signal 

            if(Flag == 1) 
            {
                check = fprintf(log,"Child %d\n", counter);
                if(check < 0) { 
                    printf("error in writing to file as parent\n");
                    exit(1);
                }
                check = fflush(log); //esures the buffer is flushed and data written to the file immediatly 
                if(check != 0) { 
                    printf("error in flushing stream\n");
                    exit(1);
                }

                check = kill(parent_pid,SIGUSR2); //sends SIGUSR2 signal to the parent
                if(check == -1) { 
                    printf("error in sending signal to parent\n");
                    exit(1);
                }
                counter++;
                Flag = 0;
            }
            if(GraceFail == 1) //used to fail gracefully if parent terminates early
            {
                return 1;
            }
        }
    }
    fclose(log);
    return 0;

}