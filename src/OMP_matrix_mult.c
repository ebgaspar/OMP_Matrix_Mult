/*
 ============================================================================
 Name        : OMP_matrix_mult.c
 Author      : Eduardo
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "timer.h"

#define N 9

typedef double TYPE ;

void create_matrix( const int NLA , const int NCA , const int NCB ,
	TYPE A[ ][ NCA ] , TYPE B[ ][ NCB ] ) ;
void print_matrix( const int NLA , const int NCB , const TYPE C[ ][ NCB ] ) ;

int main( int argc , char **argv )
{

    TYPE a[ N ][ N ] ;
    TYPE b[ N ][ N ] ;
    TYPE c[ N ][ N ] ;

    omp_set_num_threads( omp_get_num_procs( ) ) ;
    create_matrix( N , N , N , a , b ) ;

    print_matrix( N , N , a ) ;
    fputs( "\n", stdout ) ;

    print_matrix( N , N , b ) ;
    fputs( "\n", stdout ) ;

    int i , j , k ;

#pragma omp parallel for //private(i,j,k) shared(a,b,c)
    for ( i = 0 ; i < N ; ++i )
    {
	for ( j = 0 ; j < N ; ++j )
	{
	    c[ i ][ j ] = 0 ;

	    for ( k = 0 ; k < N ; ++k )
	    {
		c[ i ][ j ] += a[ i ][ k ] * b[ k ][ j ] ;
	    }
	}
    }

    print_matrix( N , N , c ) ;

    return 0 ;

}

void print_matrix( const int NLA , const int NCB , const TYPE C[ ][ NCB ] )
{
    for ( int i = 0 ; i < NLA ; ++i )
    {
	for ( int j = 0 ; j < NCB ; ++j )
	{
	    fprintf( stdout , "%.3f " , C[ i ][ j ] ) ;
	}
	fprintf( stdout , "\n" ) ;
    }
}

void create_matrix( const int NLA , const int NCA , const int NCB ,
	TYPE A[ ][ NCA ] , TYPE B[ ][ NCB ] )
{
    TYPE a = (TYPE) NCA ;

    for ( int i = 0 ; i < NLA ; ++i )
    {
	for ( int j = 0 ; j < NCA ; ++j )
	{
	    A[ i ][ j ] = ( (TYPE) rand( ) / (TYPE) ( RAND_MAX ) ) * a ;
	}
    }

    fprintf( stdout , "\n" ) ;

    for ( int i = 0 ; i < NCA ; i++ )
    {
	for ( int j = 0 ; j < NCB ; j++ )
	{
	    B[ i ][ j ] = ( (TYPE) rand( ) / (TYPE) ( RAND_MAX ) ) * a ;
	}
    }
}

