  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <time.h>
  #include <ctype.h>

  /*
    Stores the RGB values of a pixel
  */

  typedef struct Pixel{
    int red;
    int green;
    int blue;
  }Pixel; 

  /*
    Stores comments of the PPM file
  */

  struct Comments
  {
    char comment[80];
    struct Comments* next; 
  }Comments;

  /*
    Stores the contents of a PPM file
  */

  typedef struct PPM{
    /* Done: Question 1 */  
    struct Pixel*** matrix;
    char* magic_number[3];
    int max_color_value,height,width; 
  }PPM;

  struct Comments *head, *first_comment, *temp = 0;

  /*
    Adds comment to the head of the linked list
  */

  void addToHead(char * comment)
  {
    temp = (struct Comments *) malloc(sizeof(struct Comments));

    for (int i = 0; i < strlen(comment);i++)
    {
      temp->comment[i] = comment[i];
    }

    if (first_comment == 0)
    {
      first_comment = temp;
    }
    else
    {
      head->next = temp;
    }

    head = temp;
  }
  
  /*
    Returns the PPM struct from the file fd
  */
 
  PPM* getPPM(FILE* fd)
  {	  
    char newline;
    struct PPM* ppm = (struct PPM*) malloc(sizeof(struct PPM));	

    /* Done: Question 2a */

    fgets(ppm->magic_number,sizeof(ppm->magic_number),fd);

    if (strcmp("P3\n",ppm->magic_number) != 0)              //Check if file is a valid PPM file i.e. if the header is P3
    { 
      fprintf(stderr,"Not a valid PPM file. \n");
      return NULL;
    }

    char scan[1];
    scan[0] = fgetc(fd);

    if (scan[0] == '#')
    {
      while (scan[0] == '#')
      {
        char comm[80];
        fgets(comm,sizeof(comm),fd);
        addToHead(scan);
        addToHead(comm);
        scan[0] = fgetc(fd);
      }
      fseek(fd, -1, SEEK_CUR);                                      //moves the cursor in the file one character back
    }

   fscanf(fd,"%i %i" ,&ppm->width,&ppm->height);
   fscanf(fd,"%c ",&newline);
   fscanf(fd," %i ",&ppm->max_color_value);       
   ppm->matrix = calloc(ppm->width,sizeof(struct Pixel*));       //allocates memory to ppm->width elements of the matrix, each memory block of size struct Pixel and initializes memory to 0

   for (int i = 0; i < ppm->width;i++)
   {
     ppm ->matrix[i] = calloc(ppm->height,sizeof(struct Pixel*));   //allocates memory to ppm->height elements of each element in the array, each block of size struxt Pixel and initializes memory to 0

     for (int j = 0;j < ppm->height;j++)
     { 
       struct Pixel * pixel = (struct Pixel *) malloc (sizeof(struct Pixel*));
       fscanf(fd,"%i %i %i", &pixel->red,&pixel->green,&pixel->blue);
       ppm->matrix[i][j] = pixel;
     }      
   }
  return ppm; 
 }

  /*
    Prints the linked list Comments
  */

void Print()
{
  temp = first_comment;
  while(temp!=NULL)
  {
    printf("%s",temp->comment);
    temp = temp->next;
  }
}
  
void deleteList(struct Comments** head_comments)
{
 
  struct Comments* current = *head_comments;
  struct Comments* next_comment = NULL;
 
  while (current != NULL) 
  {
      next_comment = current->next;
      free(current);
      current = next_comment;
  }   
  *head_comments = NULL;
}
  /*
    Prints a PPM struct in the format of a PPM file
  */

  void showPPM(PPM* ppm){

    /* Done: Question 2b */
    /*
      Prints all headers first
    */

    printf("%s",ppm->magic_number);
    Print();
    printf("\n%i %i \n%i\n",ppm->width,ppm->height,ppm->max_color_value);

    /*
     Prints the matrix
    */ 

    for (int i = 0; i < ppm->width; i++)
    { 
      for (int j =0;j < ppm->height; j++)
      { 
        printf("%i %i %i \n",ppm->matrix[i][j]->red,ppm->matrix[i][j]->green,ppm->matrix[i][j]->blue);
      }
    }
    
  }


  /*
    Loads a file and returns it
    Prints error message and returns NULL if file can't be found or isn't a valid PPM
  */
  PPM* loadPPMFromFile(char* filename){
    FILE* file;

    /* Done: step 1, open the file */

    file = fopen(filename, "r");

    /* Done : step 2: Check that file has been loaded correctly; show error otherwise*/

    if(file != NULL)
    {
      PPM* ppm;

      /* Done: step 3, get the PPM d  ata from the file with the getPPM function */

      ppm = getPPM(file);

      if(ppm == NULL)
      {
        /* Done: step 4, display error if file cannot been parsed into a PPM struct*/

        printf("Steg: Error parsing file contents into a ppm struct\n");
        return NULL;
      }

      /* Done: step 5, close the file */

        fclose(file);

      /* step 6: return the PPM */

      return ppm;
    } 
    else
    {
      printf("Steg: Error opening file. Please check your arguments and try again. \n");
      fclose(file);
      return NULL;
    }
  }

  /*
    Write a PPM to a file : This program is not required for operation. All operations are taken care of in the function showPPM
  */

 // void writePPMtoFile(PPM* ppm){
    /* write the contents of the ppm to standard out (stdout) */
    
    /* TODO: write the headers first */

    /* TODO: then write the R G B pixel values */
//  }


  /*
    Encodes text into red field of PPM
    Returns the encoded PPM
  */

  PPM* encode(char* text, PPM* i){	

    /* Done: Question 2c */ 

    fprintf(stderr,"Please enter a seed value. \n");
    int seed; 
    scanf("%i",&seed);
    srand(seed);                                                            //Takes in a seed value to get the correct random values
    int randomheight = rand() % i->height;
    int randomwidth = rand() % i->width;
    i->matrix[randomwidth][randomheight]->green = strlen(text);              //Length of text encoded in the green pixel 
    
    for (int j = 0;j <= strlen(text);j++)
    {
      randomheight = rand() % i->height;
      randomwidth = rand() % i->width;
      int character_as_ascii = (int) text[j];
      i->matrix[randomwidth][randomheight]->red = character_as_ascii;
    }

    return i;
  }


  /*
    Compares 2 PPM structs and decodes the message hidden within
    Returns the decoded message if the images have the same dimensions
    Returns NULL otherwise
  */

  char* decode(PPM* i1)
  {                                  

    /* Done: Question 2d */
    int seed;
    printf("Please enter the seed to decode the message: \n");
    scanf("%i",&seed);
    srand(seed);
    int randomheight = rand() % i1->height;
    int randomwidth = rand() % i1->width;
    int length; 
    length = i1->matrix[randomwidth][randomheight]->green;        //length is decoded from the metadata encoded along with the message
    char* decodedMsg = malloc(length * (sizeof(char)));
    int j = 0;
    
    do 
    { 
      int height = rand() % i1->height;
      int width = rand() % i1->width;
      decodedMsg[j] = i1->matrix[width][height]->red;
      j++; 
    }while (j < length);

    decodedMsg[length - 1] = '\0';    //last element of decodedMsg is \0
    return decodedMsg;
  }

 void PrintHelp(char * executable)
 {
   fprintf(stderr,"To encode a message in a ppm file, the format is %s e <file-location> \n To decode a message from a ppm file, the format is %s d <file-location>\n",executable,executable);
 }

  /* Done: Question 3 */
  int main(int argc, char* argv[])
  {
    
    /* check arguments */
    switch(argc) {
    case 1:
      fprintf(stderr,"Steg: Incorrect number of arguments.\n");
      PrintHelp(argv[0]);
      exit(0);    
      break;
    case 2:
      /* Done: not enough arguments, print an error message */
      fprintf(stderr,"Steg: Incorrect number of arguments.\n");
      PrintHelp(argv[0]);
      exit(0);    
      break;
    case 3:

      if(strcmp(argv[1], "e") == 0) //Argument "e" - encode PPM
      {
        PPM* ppm = loadPPMFromFile(argv[2]);
        /*Check that PPM is valid; continue if it is, exit otherwise */
        if(ppm != NULL){
          PPM* encodedPPM;

          /* TODO: encode the ppm with the text and assign to encodedPPM */

            fprintf(stderr,"Enter the message to encode: \n");
            char* message = malloc(100 * sizeof(char));
            fgets(message,100,stdin); 
	          message = realloc(message,strlen(message));
            encodedPPM = encode(message,ppm);

          /*Check that no error occured*/

          if(encodedPPM == NULL)
          {
            return EXIT_FAILURE;
          }
          else 
          {

            /* TODO: print a confirmation that encoding was successful */

            fprintf(stderr,"Steg: Encoding is complete. \n");

            /* TODO: print the PPM to standard output with showPPM */

            showPPM(encodedPPM);
            free(message);
	    *message = NULL;
            deleteList(&head);
            return EXIT_SUCCESS;				
          }
        } else {					
          return EXIT_FAILURE;
        }		
      }
      else if(strcmp(argv[1], "d") == 0) //Argument "d" - decode PPM
      {
        PPM* encodedPPM;

        /* TODO: get comparison file filename from argv, load it with 
          loadPPMFromFile then assign to comparisonPPM */                                         
        /* This program does not need the original file to decode*/

        /* Done: get encoded file filename from argv, load it with
          loadPPMFromFile then assign to encodedPPM */

          encodedPPM = loadPPMFromFile(argv[2]);     

        /*Check both PPMs are valid; continue if so, exit otherwise */

        if(encodedPPM != NULL)
        {
          char* decodedMsg;

          /* TODO: decode the encodedPPM with the comparisonPPM and assign to decodedMsg */

          decodedMsg = decode(encodedPPM);

          /*Check that the message has been decoded*/

          if(decodedMsg != NULL)
          {
            /* Done: print a confirmation message that the message was decoded */ 

            fprintf(stderr,"The message was decoded.\n");

            /* Done: print the decoded message */
           
            fprintf(stderr,"\nThe decoded message is - %s\n",decodedMsg);  
            free(decodedMsg);
	    deleteList(&head);
	    *decodedMsg = NULL;
            return EXIT_SUCCESS;
          }

          else 
          {
           fprintf(stderr,"Steg: There was an error in decoding the message. Please try again\n");
           return EXIT_FAILURE;
          }				
        }
        else 
        {
          fprintf(stderr,"Steg: Please check the PPM image and try again \n");
          return EXIT_FAILURE;
        }			
      }
      else 
      {
        fprintf(stderr, "Steg: Unrecognised or incomplete command line.\n\n");
        PrintHelp(argv[0]);
        return EXIT_FAILURE;			
      }
      break;
    default:
      PrintHelp(argv[0]);
      fprintf(stderr, "Steg: Unrecognised or incomplete command line.\n\n");
      return EXIT_FAILURE;
    }
  }
