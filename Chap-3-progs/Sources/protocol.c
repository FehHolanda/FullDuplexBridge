
#include "protocol.h"
#include <stdio.h>


void wait_for_event(event_type *event){
    event = frame_arrival;
}

/* Fetch a packet from the network layer for transmission on the channel. */
void from_network_layer(packet *p){

    for(int i=0;i<MAX_PKT;i++) p->data[i] = i+10;
    
}

/* Deliver information from an inbound frame to the network layer. */
void to_network_layer(packet *p){

        for(int i=0;i<MAX_PKT;i++) printf("%d \n",p->data[i]);

}

/* Go get an inbound frame from the physical layer and copy it to r. */
void from_physical_layer(frame *r){

    r->ack=0;
    r->seq=0;
    for(int i=0;i<MAX_PKT;i++) r->info.data[i] = i+30;

}

/* Pass the frame to the physical layer for transmission. */
void to_physical_layer(frame *s){

    printf("ACK:%d\nSEQ:%d\n",s->ack,s->seq);
    for(int i=0;i<MAX_PKT;i++) printf("%d \n",s->info.data[i]);

}

/* Start the clock running and enable the timeout event. */
void start_timer(seq_nr k){

}

/* Stop the clock and disable the timeout event. */
void stop_timer(seq_nr k){

}

/* Start an auxiliary timer and enable the ack_timeout event. */
void start_ack_timer(void){

}

/* Stop the auxiliary timer and disable the ack_timeout event. */
void stop_ack_timer(void){

}

/* Allow the network layer to cause a network_layer_ready event. */
void enable_network_layer(void){

}

/* Forbid the network layer from causing a network_layer_ready event. */
void disable_network_layer(void){
    
}