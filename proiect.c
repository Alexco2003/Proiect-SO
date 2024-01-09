#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

#define number_doctors 5
#define number_patients 30
#define maximum_consultation_time 5
#define maximum_waiting_time 10

typedef struct {
    int id;
    pthread_mutex_t mutex;
} Doctor;

Doctor doctors[number_doctors];
 
pthread_t patients[number_patients];

void display_welcome_message() {
    	printf("Welcome to Private Medical Office \"AlexCo\".\n");
	printf("Today, we have %d expert doctors ready to assist you.\n", number_doctors);
	printf("The number of patients today is %d.\n", number_patients);
	printf("The maximum time allocated for a consultation is %d seconds.\n", 	maximum_consultation_time);
	printf("The maximum waiting time for a patient before leaving home is %d seconds.\n", maximum_waiting_time);
	printf("\n");

}

void * patient_function ( void * patient_id )
{
int * id = ( int *) patient_id ;
time_t start_waiting_time = time(NULL);
while(1)
{ 

time_t current_time = time(NULL);
            if (current_time - start_waiting_time > maximum_waiting_time) {
                printf("Patient %d: Leaving due to excessive wait time\n", *id);
                break;


}

int chosen_doctor=-1;
for (int i=0; i<number_doctors; i++)
{
if (pthread_mutex_trylock(&(doctors[i].mutex)) == 0) {
                chosen_doctor = i;
                break;
            }
}

if (chosen_doctor!=-1)
{

int consultation_time = rand() % maximum_consultation_time + 1;
sleep(consultation_time);
            printf("Patient %d: Visiting Doctor %d\n", *id, chosen_doctor + 1);
            printf("Patient %d: Consultation time: %d seconds\n", *id, consultation_time);
            printf("Patient %d: Time waited for doctor availability: %ld seconds\n", *id, current_time - start_waiting_time);
pthread_mutex_unlock(&(doctors[chosen_doctor].mutex));
break;

}





}


return NULL ;
}



int main()
{ display_welcome_message();

for (int i = 0; i < number_doctors; i++) {
        if ( pthread_mutex_init (&doctors[i].mutex , NULL )) {
perror ( NULL );
return errno ;
}
        doctors[i].id = i+1;
    }
    
    int id_patients[number_patients];
    for(int i=0;i<number_patients;i++)
{
id_patients[i]=i+1;
}

for(int i=0;i<number_patients;i++)
{

if ( pthread_create (&patients[i] , NULL , patient_function , &id_patients[i])) {
perror ( NULL );
return errno ;
}
}


for(int i=0;i<number_patients;i++)
   {
            if ( pthread_join ( patients[i] , NULL )) {
perror ( NULL );
return errno ;
}
        }
    

for (int i = 0; i < number_doctors; i++) {
        pthread_mutex_destroy (&doctors[i].mutex);
        doctors[i].id = -1;
    }

return 0;


}
