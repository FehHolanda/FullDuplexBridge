
#include "p1.h"

void sender1()
{
  frame s;	/* buffer for an outbound frame */
  packet buffer;	/* buffer for an outbound packet */

  for (int i=0;i<2;i++) {
        from_network_layer(&buffer);	/* go get something to send */
        s.info = buffer;	/* copy it into s for transmission */
        to_physical_layer(&s);	/* send it on its way */
       
       
       //feedback
        receiver1();
  
  }	/* tomorrow, and tomorrow, and tomorrow,
 	   Creeps in this petty pace from day to day
	   To the last syllable of recorded time;
	        - Macbeth, V, v */
 
}

void receiver1(void)
{
  frame r;
  event_type event;	/* filled in by wait, but not used here */
  boolean flag = true;

  while (flag) {
        wait_for_event(&event);	/* only possibility is frame_arrival */
        from_physical_layer(&r);	/* go get the inbound frame */
        to_network_layer(&r.info);	/* pass the data to the network layer */
        flag = false;
  }
}
