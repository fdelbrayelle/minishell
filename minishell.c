/*
  Auteur : fdelbrayelle
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <string.h> 

#define TAILLE_MAX_COMMANDE 1024 
#define NBRE_MAX_COMMANDE 30 

void lire_commandes(int* argc,char*** argv)
{ 
  int i; 
  int blanc; 
  char* commande=(char*)malloc(TAILLE_MAX_COMMANDE*sizeof(char)); 
  if( *argv != NULL)
    free((*argv));
  *argv=(char**)malloc(NBRE_MAX_COMMANDE*sizeof(char*)); 
  commande=fgets (commande, TAILLE_MAX_COMMANDE, stdin); 
  *argc=0; 
  blanc=1; 
  i=0; 
  while( commande[i] != '\n' )
    { 
      switch( commande[i] ) { 
      case ' ' : blanc=1; 
	commande[i]='\0'; 
	break; 
      case '&' : (*argv)[*argc]=&commande[i]; 
	(*argc)++; commande[i+1]='\0'; 
	return; 
      default : if( blanc == 1 ) { 
	  blanc=0; 
	  (*argv)[*argc]=&commande[i]; 
	  (*argc)++; } 
	break;
      } 
      i++; 
    }
  commande[i]='\0';
  (*argv)[*argc]=NULL;
} 

int position(int* argc,char*** argv)
{
  int i=0;
  while (i<*argc)
    {
      if(strcmp("|",(*argv)[i])==0)
	return i;
      i++;
    }
  return -1;
}

int main()
{ 
  int i,j,k,status,status2,p[2],res1,res2;
  pid_t pid;
  int argc; 
  char** argv=NULL;
  int l;
  
  printf("\n      ________   ________    _________  ____________;_\n");
  printf("     - ______ \\ - ______ \\ / _____   //.  .  ._______/\n");
  printf("     / /     / // /     / //_/     / // ___   /\n");
  printf("    / /     / // /     / /       .-'//_/|_/,-'\n");
  printf("   / /     / // /     / /     .-'.-'\n");
  printf("  / /     / // /     / /     / /\n");
  printf(" / /     / // /     / /     / /\n");
  printf("/ /_____/ // /_____/ /     / /\n");
  printf("\\________- \\________-     /_/\n\n");
  printf("Bienvenue sur le Minishell 007 !\n");
  printf("(Ctrl+C ou exit pour quitter...)\n\n");

  do
    {
      printf ("] S h e l l [ $ ");
      lire_commandes(&argc,&argv);       
      if(strcmp("exit",argv[0])!=0)
	{
	  for(l=argc-1;l>=0;l--)
	    {
	      if(strcmp(argv[l],"|")==0)
		{
		  argv[l]=NULL;
		  if(fork()==0)
		    {
		      pipe(p);
		      if(fork()==0)
			{
			  close(p[0]);
			  close(STDOUT_FILENO);
			  res1=dup(p[1]);
			  close(p[1]);
			  execvp(argv[0],argv);
			  exit(status2); 
			}
		      close(STDIN_FILENO);
		      res2=dup(p[0]);
		      close(p[0]);
		      execvp(argv[l+1],&argv[l+1]);
		      exit(status);
	    
		    }
		}
	      if(strcmp(argv[l],"<")==0)
		{
		  argv[l]=NULL;
		  l++;
		  int desfic=open(argv[l],S_IROTH);
		  close(STDIN_FILENO);
		  dup(desfic);
		  close(desfic);
		  execvp(argv[0],argv);
		}
	      if(strcmp(argv[l],">")==0)
		{
		  argv[l]=NULL;
		  l++;
		  int desfic=open(argv[l],O_CREAT,S_IROTH | S_IRWXU);
		  close(STDOUT_FILENO);
		  dup(desfic);
		  close(desfic);
		  execvp(argv[0],argv);
		}
	      if(l==0)
		if ((pid=fork())==0)
		  {
		    execvp(argv[0],argv);
		    exit(status);
		  }
	      if(strcmp("&",argv[argc-1])!=0)
		waitpid(pid,&status,0); 
	    }
	}
    } while (argc == 0 || strcmp("exit",argv[0]) != 0); 
  printf("A bientot !\n");
}
