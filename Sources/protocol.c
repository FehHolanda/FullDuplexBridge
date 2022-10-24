
#include "../Project_Headers/protocol.h"
#include "../Project_Headers/buffer.h"
#include "../Project_Headers/uart.h"
#include "../Project_Headers/intrpt.h"

frame feedback;
extern boolean event_ready;
extern boolean stoped_timer;
extern event_type event_save;
Buffer buffer_in_terminal;
Buffer buffer_out_terminal;
Buffer buffer_in_Serial;
Buffer buffer_out_Serial;
int id=10;


void wait_for_event(event_type *event){
    while(!event_ready);
    *event = event_save;
    event_ready=false;
}

/* Fetch a packet from the network layer for transmission on the channel. */
void from_network_layer(packet *p){
    p->data[MAX_PKT-1] = 0;
    for(int i=0;i<MAX_PKT-1;i++) p->data[i] = id;
     p->data[MAX_PKT-1] += id; 
    id++;
    /*
    p->data[MAX_PKT-1] = 0; 
    for(int i=0;i<MAX_PKT-1;i++) {
        while(buffer_in_Serial.empty);
        int aux =  buffer_in_Serial.Buff[buffer_in_Serial.index_start];
        p->data[i] = aux;
        p->data[MAX_PKT-1] += aux;
        buffer.remove()
    }   
    
    */
            
}

/* Deliver information from an inbound frame to the network layer. */
void to_network_layer(packet *p){
    									
    for(int i=0;i<MAX_PKT-1;i++) putchar_terminal(p->data[i],&buffer_out_terminal);
 
}

/* Go get an inbound frame from the physical layer and copy it to r. */
void from_physical_layer(frame *r){
    
    r->ack = buffer_in_Serial.Buff[buffer_in_Serial.index_start];
    buffer_remove(&buffer_in_Serial);
    r->ack = 0;
    buffer_remove(&buffer_in_Serial);
    for(int i=0;i<MAX_PKT;i++) {
         r->info.data[i] = buffer_in_Serial.Buff[buffer_in_Serial.index_start];
        buffer_remove(&buffer_in_Serial);
    }  
}

/* Pass the frame to the physical layer for transmission. */
void to_physical_layer(frame *s){

    //printf("\nMensagem Enviada:\n");
    //printf("ACK:%d\nSEQ:%d\n",s->ack,s->seq);
    //for(int i=0;i<MAX_PKT;i++) printf("%d \n",s->info.data[i]);

        
    putchar_serial(s->ack,&buffer_out_Serial);
    putchar_serial(s->seq,&buffer_out_Serial);
    for(int i=0;i<MAX_PKT;i++) putchar_serial(s->info.data[i],&buffer_out_Serial);
   

}

/* Start the clock running and enable the timeout event. */
void start_timer(seq_nr k){
    Start_Timer();
    stoped_timer = false;
}

/* Stop the clock and disable the timeout event. */
void stop_timer(seq_nr k){
    stoped_timer = true;
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