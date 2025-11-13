#include "moduloSincro.h"



void *producer (void *arg){
    int i, r; //declara dos variables de tipo entero, i y r
    int my_id = *((int *) arg); //declara una
    int count = 0; //declara e inicializa count en 0

    for (i = 0; i < 10; i++) {

        if ((r = pthread_mutex_lock (&buf_mutex)) != 0) {
            fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
        }
            while (!buffers_available) 
                pthread_cond_wait (&buf_cond, &buf_mutex);

            int j = buffer_index;
            buffer_index++;
            if (buffer_index == MAX_BUFFERS)
                buffer_index = 0;
            buffers_available--;

            sprintf (buf [j], "Thread %d: %d\n", my_id, ++count);
            lines_to_print++;

            pthread_cond_signal (&spool_cond);

        if ((r = pthread_mutex_unlock (&buf_mutex)) != 0) {
            fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
        }
    
        sleep (1);
    }
}

void *spooler (void *arg){
    int r;

    while (1) {  
        if ((r = pthread_mutex_lock (&buf_mutex)) != 0) {
            fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
        }
            while (!lines_to_print) 
                pthread_cond_wait (&spool_cond, &buf_mutex);

            printf ("%s", buf [buffer_print_index]);
            lines_to_print--;

            buffer_print_index++;
            if (buffer_print_index == MAX_BUFFERS)
               buffer_print_index = 0;

            buffers_available++;
            pthread_cond_signal (&buf_cond);

        if ((r = pthread_mutex_unlock (&buf_mutex)) != 0) {
            fprintf (stderr, "Error = %d (%s)\n", r, strerror (r)); exit (1);
        }

    }
}
