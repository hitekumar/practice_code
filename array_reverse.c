 #include <stdio.h>
  
 typedef int my_type;
 my_type my_array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9 ,10};
  
 void revrese_array(void **head, int num_elements)
 {   
    int i;
    my_type * start = (my_type *)head;
    my_type tmp;
    for (i = 0; i < (num_elements/2) +1 ; i++)
    {
        tmp = start[i];
         start[i] = start[num_elements -i];
         start[num_elements -i] =tmp;
      }
 }
  
 void print_array()
 {
     int i;
     
    for (i = 0; i < 10; i++)
    {
        printf("%d\n", my_array[i]);
    }
 }
  
 int main()
 {
    print_array();
    printf("Reversing\n");
    revrese_array(my_array, 10);
    print_array();
 }
