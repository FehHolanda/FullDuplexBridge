/* Protocol 2 (stop-and-wait) also provides for a one-directional flow of data from
   sender to receiver. The communication channel is once again assumed to be error
   free, as in protocol 1. However, this time, the receiver has only a finite buffer
   capacity and a finite procesing speed, so the protocol must explicitly prevent 
   the sender from flooding the receiver with data faster than it can be handled. */

#include "protocol.h"
#include "p2.h"
#define MAX_SEQ 1
void sender2(void)
{
  frame s;	/* buffer for an outbound frame */
  packet buffer;	/* buffer for an outbound packet */
  event_type event;	/* frame_arrival is the only possibility */

  for (int i =0;i<3;i++) {
        from_network_layer(&buffer);	/* go get something to send */
        s.info = buffer;	/* copy it into s for transmission */
        to_physical_layer(&s);	/* bye bye little frame */


        /*feedback*/
        receiver2();


        wait_for_event(&event);	/* do not proceed until given the go ahead */
  }
}

void receiver2(void)
{
  frame r, s;	/* buffers for frames */
  event_type event;	/* frame_arrival is the only possibility */
  boolean control = true;

  while (control) {
        wait_for_event(&event);	/* only possibility is frame_arrival */
        from_physical_layer(&r);	/* go get the inbound frame */
        to_network_layer(&r.info);	/* pass the data to the network layer */
        to_physical_layer(&s);	/* send a dummy frame to awaken sender */
        control = false;
  }
  
}

