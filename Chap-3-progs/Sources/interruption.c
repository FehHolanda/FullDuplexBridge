
#include <signal.h>
#include <stdio.h>
#include "protocol.h"
 
volatile sig_atomic_t gSignalStatus;
boolean event_ready; 


void signal_handler(int signal)
{
    if(signal == SIGINT) event_ready=true;
}
 
int interruption_func(event_type *event)
{
  signal(SIGINT, signal_handler); 
  
  if (event == frame_arrival) raise(SIGINT);

}