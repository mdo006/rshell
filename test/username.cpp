
// #include <limits.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// int main()
// {
//   char hostname[HOST_NAME_MAX];
//   char username[LOGIN_NAME_MAX];
//   int result;
//   result = gethostname(hostname, HOST_NAME_MAX);
//   if (result)
//     {
//       perror("gethostname");
//       return EXIT_FAILURE;
//     }
//   result = getlogin_r(username, LOGIN_NAME_MAX);
//   if (result)
//     {
//       perror("getlogin_r");
//       return EXIT_FAILURE;
//     }
//   result = printf("Hello %s, you are logged in to %s.\n",
//                   username, hostname);
//   if (result < 0)
//     {
//       perror("printf");
//       return EXIT_FAILURE;
//     }
//   return EXIT_SUCCESS;
// }


// #include <sys/types.h> 
// #include <pwd.h> 

// #include <iostream>
// #include <sys/unistd.h>
// #include<stdlib.h>

/*

char * getlogin(void);
int getlogin_r(char*name, size_t namesize);

int gethostname(char *name, size_t len);
*/

    // name =(char *)malloc(10 * sizeof(char));
    // name = getlogin();
    // if ((name = getlogin()) == NULL)
    // perror("__getlogin1() error");
    // else printf("__getlogin1() returned %s\n", name);
    // char * getlogin(void);
    // int getlogin_r(char*name, size_t namesize);
    // if (!name)
    // {
    //     perror("getlogin() error");
    // }
    // else
    // {
    //     printf("%s\n", name);
    // }
    // // 

#include <stdio.h> 
#include <unistd.h> 
#include<stdlib.h>
using namespace std;

int main()
{
    char *name;

    char hostname[80];
    gethostname(hostname, sizeof hostname);
    name = getenv("USER");
    printf("%s\n",name);
 
    printf("%s\n", hostname);
 
}




