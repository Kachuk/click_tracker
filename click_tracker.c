#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <winuser.h>

#define SCREEN_VECTOR_COLUMNS GetSystemMetrics(SM_CXSCREEN)/10

#define SCREEN_VECTOR_ROWS GetSystemMetrics(SM_CYSCREEN)/10



/**typedef struct tagPOINT { // POINT struct
  LONG x;
  LONG y;
} POINT, *PPOINT;
*/


void initialize_matrix(int[][SCREEN_VECTOR_COLUMNS], int, int);

void show_matrix(int[][SCREEN_VECTOR_COLUMNS], int, int);




int main(){


    FILE *mp;




	short int left_click_status_reference = GetKeyState(VK_LBUTTON);
	short int left_click_status;
	POINT cursor_position;

	short int c_key_status_reference =  GetKeyState(0x43);
    short int c_key_status;



    int screen_sectors_matrix[SCREEN_VECTOR_ROWS][SCREEN_VECTOR_COLUMNS];

    /// variable-sized object cannot  be initialized like this array[var]={0};, so we need to do it manually


    if ( (mp=fopen("click_matrix.dat", "rb")) == 0 ){

        printf("no");


        initialize_matrix(screen_sectors_matrix , SCREEN_VECTOR_ROWS, SCREEN_VECTOR_COLUMNS);
    } else{
        printf("yes");
        fread(screen_sectors_matrix, sizeof(screen_sectors_matrix), 1, mp);


    }
    fclose(mp);




    while (TRUE){

            left_click_status = GetKeyState(VK_LBUTTON);

            if (left_click_status_reference != left_click_status){
            	left_click_status_reference = left_click_status;

            	if (left_click_status<0){ ///GetKeyState returns a negative value if the key is pressed

                    GetCursorPos(&cursor_position); /// for what i have tested, this function never returns 1980,1080, this is good because we can use the values as index for the matrix

                    printf("%li   %li \n", cursor_position.x/10,cursor_position.y/10 );

                    screen_sectors_matrix[cursor_position.y/10][cursor_position.x/10]++;



            	}

            }

            ///let's set a break for the loop when pressed the "c" key
            ///alphabet virtual-key-codes begin at 0x41="A" , so "C" will be "0x43"

            c_key_status = GetAsyncKeyState(0x43);


            if (c_key_status_reference != c_key_status){
            	c_key_status_reference = c_key_status;

            	if (c_key_status<0){ ///GetAsyncKeyState returns a negative value if the key is pressed

                   break;


            	}

            }

            Sleep(0.01);




    }



    getchar();


    if ( (mp=fopen("click_matrix.dat", "wb")) == 0 ){

        printf("error");


    } else{
        printf("yes");
        fwrite(screen_sectors_matrix, sizeof(screen_sectors_matrix), 1, mp);


    }
    fclose(mp);

    return 0;

}


void initialize_matrix(int matrix[][SCREEN_VECTOR_COLUMNS], int rows, int columns){
    int j,i;

    for (j=0; j<rows ; j++ ){

        for (i=0; i<columns; i++ ){

            matrix[j][i]=0;

        }



    }
}


void show_matrix(int matrix[][SCREEN_VECTOR_COLUMNS], int rows, int columns){
    int j,i;

     for (j=0; j<rows ; j++ ){

        for (i=0; i<columns; i++ ){

            printf("%d-", matrix[j][i]);


        }

        printf("\n");

    }

}

