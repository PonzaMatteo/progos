#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>

#include "program.h"

void generate_daemon();

int run_program(char *cmd)
{
  if (init_client() < 0)
  {
    cond_print("[Daemon isn't running]\n");
    generate_daemon();
  }

  if (init_client() == OK_STATUS)
  {
    cond_print("[Ready for execution]\n");
    cond_print("\n---------    output: \"%s\"    ---------\n", cmd);
    run_cmd(cmd);
    int i;
    for (i = 0; i < abs(strlen("---------    output:\"\"    ---------n") + strlen(cmd)); i++)
      cond_print("-", cmd);
    cond_print("\n");
  }
  else
  {
    fprintf(stderr, "Error: daemon still not running\n");
    return EXIT_FAILURE;
  }
  return OK_STATUS;
}

void generate_daemon()
{
  cond_print("[Generating Daemon]\n");

  pid_t fid = fork();
  if (fid < 0)
  {
    fprintf(stderr, "Error in creating daemon proces\n");
    exit(EXIT_FAILURE);
  }
  else if (fid == 0)
  {
    if (init_server() == FAIL_STATUS)
    {
      exit(EXIT_FAILURE);
    }
    int r = daemon(1 - DAEMON_CH_DIR, 1 - DAEMON_CLOSE_OUT); //DA QUI IN POI é CODICE DEL DEMONE
    if (r < 0)
    {
      fprintf(stderr, "Error in creating daemon proces: [%d]\n", r);
      exit(EXIT_FAILURE);
    }
    printf("[Daemon is running. Pid:%d ] \n", getpid());
    start_listening(); // Quando finisce di ascoltare deve eliminare la coda e terminare con successo!!

    if (delete_server() < 0)
    {
      fprintf(stderr, "Error in terminating daemon\n");
      exit(EXIT_FAILURE);
    }
    cond_print("[Deamon killed, queue deleted]\n");
    exit(EXIT_SUCCESS);
  }
  else
  {
    my_wait(&fid);
  }
}
int esegui_e_logga(char *cmd)
{
  char *msgtxt = malloc(sizeof(char) * MAX_LEN_STAT);
  msg message;
  int c;

  if (strcmp(cmd, "stop-daemon") == 0)
    message.type = TYPE_EXIT;
  else
  {
    message.type = format;
    c = stats(cmd, msgtxt, sep, mu, names);
  }

  strcpy(message.msg_log.txt, msgtxt);
  strcpy(message.msg_log.fn, filename);

  send_msg(&message);

  free(msgtxt);
  return c;
}