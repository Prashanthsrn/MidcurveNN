/*******************************************************************************
*       FILENAME :      topo_data_resolve.c DESIGN REF :  FBD(CAD/CAPP)
*
*       DESCRIPTION :   contains all the data assignments for topo_links
*
*       FUNCTIONS   :   
*
*       AUTHOR      :   Yogesh Kulkarni
*
*       DATE        :   June 17, 1995.
*
*******************************************************************************/
 
 
/******************************************************************************
                       INCLUDE FILES
******************************************************************************/
 
#include "main_window.h"        /* Motif Declarations :header file */
#include "application.h"        /* Application Declarations :header file */
#include "classes.h"        	/* Classes Declarations :header file */
#include "graphics_phigs.h"     /* Phigs Declarations :header file */
 
/******************************************************************************
                        GLOBAL DECLARATIONS(INTERFACE)
******************************************************************************/

/*****************************************************************************
*
*       NAME    :       cfm_for_resolve()
*
*       DESCRIPTION :	Assignment of plane values takes place   
*
******************************************************************************/

void cfm_for_resolve(int id ,int id1,int tp1){

        Block *b = Get_block( currc , id);	// b is for Base block
        Block *d = Get_block( currc , id1);	// d is for Destination block
 
	// If are goes from block_id 2 to block_id 1 then this kind of arc
	// is considered as negative arc because it is in the inverse direction
	// of when it was created. For the negative arc plane assignmnets are
	// reversed. For this checking we will define neg (negative ?) as
	// a temorary variable and with help of it assign the plane values

	// we can not just change *b and *d because any way we have to extract
	// values from given *b only and with its help set values in *d


	int neg = FALSE;

	if(id > id1)neg = TRUE;	// If Id of base block is greater than
				// Id of destination then it is negative arc


	double bx_min	= b->Get_Xmin();
	double bx_mid	= b->Get_Xmid();
	double bx_max	= b->Get_Xmax();

	double by_min	= b->Get_Ymin();
	double by_mid	= b->Get_Ymid();
	double by_max	= b->Get_Ymax();

	double bz_min	= b->Get_Zmin();
	double bz_mid	= b->Get_Zmid();
	double bz_max	= b->Get_Zmax();

	switch(tp1){		

                case XMIN_MIN :
 
				d->Set_Xmin(bx_min);
				d->Set_Ymid(by_mid);
				d->Set_Zmid(bz_mid);	
				d->fix_xmin(TRUE);
				d->fix_ymid(TRUE);
				d->fix_zmid(TRUE);
                                break;
                case XMIN_MAX :
				if(neg){
					d->Set_Xmin(bx_max);
					d->fix_xmin(TRUE);
				}
				else{
					d->Set_Xmax(bx_min);
					d->fix_xmax(TRUE);
				}
                                d->Set_Ymid(by_mid);       
				d->Set_Zmid(bz_mid);	
				d->fix_ymid(TRUE);
				d->fix_zmid(TRUE);
                                break;
                case YMIN_MIN :
				d->Set_Ymin(by_min);
                                d->Set_Xmid(bx_mid);       
                                d->Set_Zmid(bz_mid);       
				d->fix_ymin(TRUE);
				d->fix_xmid(TRUE);
				d->fix_zmid(TRUE);
                                break;
                case YMIN_MAX :
				if(neg){
					d->Set_Ymin(by_max);
                                        d->fix_ymin(TRUE);
                                }
                                else{
                                        d->Set_Ymax(by_min);
                                        d->fix_ymax(TRUE);
                                }
                                d->Set_Xmid(bx_mid);       
                                d->Set_Zmid(bz_mid);       
				d->fix_xmid(TRUE);
				d->fix_zmid(TRUE);
                                break;
                case ZMIN_MIN :
				d->Set_Zmin(bz_min);
                                d->Set_Ymid(by_mid);       
                                d->Set_Xmid(bx_mid);       
				d->fix_zmin(TRUE);
				d->fix_xmid(TRUE);
				d->fix_ymid(TRUE);
                                break;
                case ZMIN_MAX :
				if(neg){
					d->Set_Zmin(bz_max);
                                        d->fix_zmin(TRUE);
                                }
                                else{
                                        d->Set_Zmax(bz_min);
                                        d->fix_zmax(TRUE);
				}
                                
                                d->Set_Ymid(by_mid);       
                                d->Set_Xmid(bx_mid);       
				d->fix_xmid(TRUE);
				d->fix_ymid(TRUE);
                                break;

		case XMAX_MIN :
				if(neg){
					d->Set_Xmax(bx_min);
                                        d->fix_xmax(TRUE);
                                }
                                else{
                                        d->Set_Xmin(bx_max);
                                        d->fix_xmin(TRUE);
                                }
                                d->Set_Ymid(by_mid);       
                                d->Set_Zmid(bz_mid);       
                                d->fix_ymid(TRUE);
                                d->fix_zmid(TRUE);
				break;
		case XMAX_MAX :
				d->Set_Xmax(bx_max);
                                d->Set_Ymid(by_mid);
                                d->Set_Zmid(bz_mid);
                                d->fix_xmax(TRUE);
                                d->fix_ymid(TRUE);
                                d->fix_zmid(TRUE);
				break;
		case YMAX_MIN :
                                if(neg){
					d->Set_Ymax(by_min);
                                        d->fix_ymax(TRUE);
                                }
                                else{
                                        d->Set_Ymin(by_max);
                                        d->fix_ymin(TRUE);
                                }
                               	d->Set_Xmid(bx_mid);
                                d->Set_Zmid(bz_mid);
                                d->fix_xmid(TRUE);
                                d->fix_zmid(TRUE);
				break;
		case YMAX_MAX :
				d->Set_Ymax(by_max);
                                d->Set_Xmid(bx_mid);
                                d->Set_Zmid(bz_mid);
                                d->fix_ymax(TRUE);
                                d->fix_xmid(TRUE);
                                d->fix_zmid(TRUE);
				break;
		case ZMAX_MIN :
                                if(neg){
					d->Set_Zmax(bz_min);
                                        d->fix_zmax(TRUE);
                                }
                                else{
                                        d->Set_Zmin(bz_max);
                                        d->fix_zmin(TRUE);
                                }
                                d->Set_Xmid(bx_mid);
                                d->Set_Ymid(by_mid);
                                d->fix_xmid(TRUE);
                                d->fix_ymid(TRUE);
				break;
		case ZMAX_MAX :
				d->Set_Zmax(bz_max);
                                d->Set_Xmid(bx_mid);
                                d->Set_Ymid(by_mid);
                                d->fix_zmax(TRUE);
                                d->fix_xmid(TRUE);
                                d->fix_ymid(TRUE);
				break;
	}
}

/*****************************************************************************
*
*       NAME    :       cm_for_resolve()
*
*       DESCRIPTION :   Assignment of plane values takes place   
*
******************************************************************************/
 
void cm_for_resolve(int id ,int id1,int tp1 ,int tp2 ,int tp3)
{
        Block *b = Get_block( currc , id);	 // b is for Base block
        Block *d = Get_block( currc , id1);     // d is for Destination block
 
        int neg = FALSE;
 
        if(id > id1)neg = TRUE; // If Id of base block is greater than
                                // Id of destination then it is negative arc
 
        double bx_min   = b->Get_Xmin();
        double bx_mid   = b->Get_Xmid();
        double bx_max   = b->Get_Xmax();
 
 
        double by_min   = b->Get_Ymin();
        double by_mid   = b->Get_Ymid();
        double by_max   = b->Get_Ymax();
 
        double bz_min   = b->Get_Zmin();
        double bz_mid   = b->Get_Zmid();
        double bz_max   = b->Get_Zmax();
 
        switch(tp1){
 
                case XMIN_MIN :
                                d->Set_Xmin(bx_min);
				d->fix_xmin(TRUE);
                                break;
                case XMIN_MAX :
                                if(neg){
					d->Set_Xmin(bx_max);
                                        d->fix_xmin(TRUE);
                                }
                                else{
                                        d->Set_Xmax(bx_min);
                                        d->fix_xmax(TRUE);
                                }
 
                                break;
                case YMIN_MIN :
                                d->Set_Ymin(by_min);
				d->fix_ymin(TRUE);
                                break;
                case YMIN_MAX :
                                if(neg){
					d->Set_Ymin(by_max);
                                        d->fix_ymin(TRUE);
                                }
                                else{
                                        d->Set_Ymax(by_min);
                                        d->fix_ymax(TRUE);
                                }
                                break;
                case ZMIN_MIN :
                                d->Set_Zmin(bz_min);
				d->fix_zmin(TRUE);
                                break;
                case ZMIN_MAX :
                                if(neg){
					d->Set_Zmin(bz_max);
                                        d->fix_zmin(TRUE);
                                }
                                else{
                                        d->Set_Zmax(bz_min);
                                        d->fix_zmax(TRUE);
                                }
 
                                break;
 
                case XMAX_MIN :
                                if(neg){
					d->Set_Xmax(bx_min);
                                        d->fix_xmax(TRUE);
                                }
                                else{
                                        d->Set_Xmin(bx_max);
                                        d->fix_xmin(TRUE);
                                }
                                break;
                case XMAX_MAX :
                                d->Set_Xmax(bx_max);
				d->fix_xmax(TRUE);
                                break;
                case YMAX_MIN :
                                if(neg){
					d->Set_Ymax(by_min);
                                        d->fix_ymax(TRUE);
                                }
                                else{
                                        d->Set_Ymin(by_max);
                                        d->fix_ymin(TRUE);
                                }
                                break;
                case YMAX_MAX :
                                d->Set_Ymax(by_max);
				d->fix_ymax(TRUE);
                                break;
                case ZMAX_MIN :
                                if(neg){
					d->Set_Zmax(bz_min);
                                        d->fix_zmax(TRUE);
                                }
                                else{
                                        d->Set_Zmin(bz_max);
                                        d->fix_zmin(TRUE);
                                }
                                break;
                case ZMAX_MAX :
                                d->Set_Zmax(bz_max);
				d->fix_zmax(TRUE);
                                break;
        }
 
        /*
                Error checking is necessary here to see if the
                same axes comes for the second plane  which is
                an error !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 
        */
 
        switch(tp2){
 
                case XMIN_MIN :
                                d->Set_Xmin(bx_min);
                                d->fix_xmin(TRUE);
                                break;
                case YMIN_MIN :
                                d->Set_Ymin(by_min);
                                d->fix_ymin(TRUE);
                                break;
                case ZMIN_MIN :
                                d->Set_Zmin(bz_min);
                                d->fix_zmin(TRUE);
                                break;
                case XMAX_MAX :
                                d->Set_Xmax(bx_max);
                                d->fix_xmax(TRUE);
                                break;
                case YMAX_MAX :
                                d->Set_Ymax(by_max);
                                d->fix_ymax(TRUE);
                                break;
                case ZMAX_MAX :
                                d->Set_Zmax(bz_max);
                                d->fix_zmax(TRUE);
                                break;
		default	:
				post_msg("Error! Choose MIN_MIN or MAX_MAX !");
				break;
        }

        switch(tp3){
 
                case XMIN_MIN :
                                d->Set_Xmin(bx_min);
                                d->fix_xmin(TRUE);
                                break;
                case YMIN_MIN :
                                d->Set_Ymin(by_min);
                                d->fix_ymin(TRUE);
                                break;
                case ZMIN_MIN :
                                d->Set_Zmin(bz_min);
                                d->fix_zmin(TRUE);
                                break;
                case XMAX_MAX :
                                d->Set_Xmax(bx_max);
                                d->fix_xmax(TRUE);
                                break;
                case YMAX_MAX :
                                d->Set_Ymax(by_max);
                                d->fix_ymax(TRUE);
                                break;
                case ZMAX_MAX :
                                d->Set_Zmax(bz_max);
                                d->fix_zmax(TRUE);
                                break;
		default	:
				post_msg("Error! Choose MIN_MIN or MAX_MAX !");
				break;
        }

}

/*****************************************************************************
*
*       NAME    :       cem_for_resolve()
*
*       DESCRIPTION :   Assignment of plane values takes place   
*
******************************************************************************/
 
void cem_for_resolve(int id ,int id1,int tp1 ,int tp2)
{

        Block *b = Get_block( currc , id);	 // b is for Base block
        Block *d = Get_block( currc , id1);     // d is for Destination block
 
        int neg = FALSE;
 
        if(id > id1)neg = TRUE; // If Id of base block is greater than
                                // Id of destination then it is negative arc
 

        double bx_min   = b->Get_Xmin();
        double bx_mid   = b->Get_Xmid();
        double bx_max   = b->Get_Xmax();
 
        double by_min   = b->Get_Ymin();
        double by_mid   = b->Get_Ymid();
        double by_max   = b->Get_Ymax();
 
        double bz_min   = b->Get_Zmin();
        double bz_mid   = b->Get_Zmid();
        double bz_max   = b->Get_Zmax();
 

        switch(tp1){
 
                case XMIN_MIN :
                                d->Set_Xmin(bx_min);
                                d->fix_xmin(TRUE);
                                break;
                case XMIN_MAX :
                                if(neg){
					d->Set_Xmin(bx_max);
                                        d->fix_xmin(TRUE);
                                }
                                else{
                                        d->Set_Xmax(bx_min);
                                        d->fix_xmax(TRUE);
                                }
 
                                break;
                case YMIN_MIN :
                                d->Set_Ymin(by_min);
                                d->fix_ymin(TRUE);
                                break;
                case YMIN_MAX :
                                if(neg){
					d->Set_Ymin(by_max);
                                        d->fix_ymin(TRUE);
                                }
                                else{
                                        d->Set_Ymax(by_min);
                                        d->fix_ymax(TRUE);
                                }
                                break;
                case ZMIN_MIN :
                                d->Set_Zmin(bz_min);
                                d->fix_zmin(TRUE);
                                break;
                case ZMIN_MAX :
                                if(neg){
					d->Set_Zmin(bz_max);
                                        d->fix_zmin(TRUE);
                                }
                                else{
                                        d->Set_Zmax(bz_min);
                                        d->fix_zmax(TRUE);
                                }
 
                                break;
 
                case XMAX_MIN :
                                if(neg){
					d->Set_Xmax(bx_min);
                                        d->fix_xmax(TRUE);
                                }
                                else{
                                        d->Set_Xmin(bx_max);
                                        d->fix_xmin(TRUE);
                                }
                                break;
                case XMAX_MAX :
                                d->Set_Xmax(bx_max);
 
                                d->fix_xmax(TRUE);
                                break;
                case YMAX_MIN :
                                if(neg){
					d->Set_Ymax(by_min);
                                        d->fix_ymax(TRUE);
                                }
                                else{
                                        d->Set_Ymin(by_max);
                                        d->fix_ymin(TRUE);
                                }
                                break;
                case YMAX_MAX :
                                d->Set_Ymax(by_max);
                                d->fix_ymax(TRUE);
                                break;
                case ZMAX_MIN :
                                if(neg){
					d->Set_Zmax(bz_min);
                                        d->fix_zmax(TRUE);
                                }
                                else{
                                        d->Set_Zmin(bz_max);
                                        d->fix_zmin(TRUE);
                                }
                                break;
                case ZMAX_MAX :
                                d->Set_Zmax(bz_max);
                                d->fix_zmax(TRUE);
                                break;
        }
 
        switch(tp2){
 
                case XMIN_MIN :
 
                                x_minf = bx_min;
				x_midf = bx_mid;
                                break;
                case XMIN_MAX :
                                x_maxf = bx_min;
				x_midf = bx_mid;
                                break;
                case YMIN_MIN :
                                y_minf = by_min;
				y_midf = by_mid;
                                break;
                case YMIN_MAX :
                                y_maxf = by_min;
				y_midf = by_mid;
                                break;
                case ZMIN_MIN :
                                z_minf = bz_min;
				z_midf = bz_mid;
                                break;
                case ZMIN_MAX :
                                z_maxf = bz_min;
				z_midf = bz_mid;
                                break;
                case XMAX_MIN :
                                x_minf = bx_max;
				x_midf = bx_mid;
                                break;
                case XMAX_MAX :
                                x_maxf = bx_max;
				x_midf = bx_mid;
                                break;
                case YMAX_MIN :
                                y_minf = by_max;
				y_midf = by_mid;
                                break;
                case YMAX_MAX :
                                y_maxf = by_max;
				y_midf = by_mid;
                                break;
                case ZMAX_MIN :
                                z_minf = bz_max;
				z_midf = bz_mid;
                                break;
                case ZMAX_MAX :
                                z_maxf = bz_max;
				z_midf = bz_mid;
                                break;
        }

}

/*****************************************************************************
*
*       NAME    :       tcm_for_resolve()
*
*       DESCRIPTION :   Assignment of plane values takes place   
*
******************************************************************************/
 
void tcm_for_resolve(int id ,int id1,int tp1,int tp2,int tp3,int tp4)
{

        Block *b = Get_block( currc , id);	 // b is for Base block
        Block *d = Get_block( currc , id1);     // d is for Destination block
 
        int neg = FALSE;
 
        if(id > id1)neg = TRUE; // If Id of base block is greater than
                                // Id of destination then it is negative arc
 

        double bx_min   = b->Get_Xmin();
        double bx_mid   = b->Get_Xmid();
        double bx_max   = b->Get_Xmax();
 
 
        double by_min   = b->Get_Ymin();
        double by_mid   = b->Get_Ymid();
        double by_max   = b->Get_Ymax();
 
        double bz_min   = b->Get_Zmin();
        double bz_mid   = b->Get_Zmid();
        double bz_max   = b->Get_Zmax();
 
 
        switch(tp1){
 
                case XMIN_MIN :
                                d->Set_Xmin(bx_min);
                                d->fix_xmin(TRUE);
                                break;
                case XMIN_MAX :
                                if(neg){
					d->Set_Xmin(bx_max);
                                        d->fix_xmin(TRUE);
                                }
                                else{
                                        d->Set_Xmax(bx_min);
                                        d->fix_xmax(TRUE);
                                }
 
                                break;
                case YMIN_MIN :
                                d->Set_Ymin(by_min);
                                d->fix_ymin(TRUE);
                                break;
                case YMIN_MAX :
                                if(neg){
					d->Set_Ymin(by_max);
                                        d->fix_ymin(TRUE);
                                }
                                else{
                                        d->Set_Ymax(by_min);
                                        d->fix_ymax(TRUE);
                                }
                                break;
                case ZMIN_MIN :
                                d->Set_Zmin(bz_min);
                                d->fix_zmin(TRUE);
                                break;
                case ZMIN_MAX :
                                if(neg){
					d->Set_Zmin(bz_max);
                                        d->fix_zmin(TRUE);
                                }
                                else{
                                        d->Set_Zmax(bz_min);
                                        d->fix_zmax(TRUE);
                                }
 
                                break;
 
                case XMAX_MIN :
                                if(neg){
					d->Set_Xmax(bx_min);
                                        d->fix_xmax(TRUE);
                                }
                                else{
                                        d->Set_Xmin(bx_max);
                                        d->fix_xmin(TRUE);
                                }
                                break;
                case XMAX_MAX :
                                d->Set_Xmax(bx_max);
 
                                d->fix_xmax(TRUE);
                                break;
                case YMAX_MIN :
                                if(neg){
					d->Set_Ymax(by_min);
                                        d->fix_ymax(TRUE);
                                }
                                else{
                                        d->Set_Ymin(by_max);
                                        d->fix_ymin(TRUE);
                                }
                                break;
                case YMAX_MAX :
                                d->Set_Ymax(by_max);
                                d->fix_ymax(TRUE);
                                break;
                case ZMAX_MIN :
                                if(neg){
					d->Set_Zmax(bz_min);
                                        d->fix_zmax(TRUE);
                                }
                                else{
                                        d->Set_Zmin(bz_max);
                                        d->fix_zmin(TRUE);
                                }
                                break;
                case ZMAX_MAX :
                                d->Set_Zmax(bz_max);
                                d->fix_zmax(TRUE);
                                break;
        }
 
        /*
                Error checking is necessary here to see if the
                same axes comes for the second plane  which is
                an error !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 
        */
 
		Length* xl;
		Length* yl;
		Length* zl;

        switch(tp2){
 
                case XMIN_MIN :
                case XMAX_MAX :
 
                      	d->Set_Xmin(bx_min);
                      	d->Set_Xmid(bx_mid);
                      	d->Set_Xmax(bx_max);

			xl = d->Get_Xlen();
                      	xl->Set_length(bx_max - bx_min);

			d->fix_xmin(TRUE);
			d->fix_xmid(TRUE);
			d->fix_xmax(TRUE);
			d->fix_xlen(TRUE);

			switch(tp3){
 
                		case YMIN_MIN :
                                	d->Set_Ymin(by_min);
                                	d->fix_ymin(TRUE);
                                	break;

                		case ZMIN_MIN :
                                	d->Set_Zmin(bz_min);
                                	d->fix_zmin(TRUE);
                                	break;

                		case YMAX_MAX :
                                	d->Set_Ymax(by_max);
                                	d->fix_ymax(TRUE);
                                	break;

                		case ZMAX_MAX :
                                	d->Set_Zmax(bz_max);
                                	d->fix_zmax(TRUE);
                                	break;

                		default :

                                post_msg("Error! Choose MIN_MIN or MAX_MAX !");
                                break;
        		}

                                break;


                case YMIN_MIN :
                case YMAX_MAX :

                        d->Set_Ymin(by_min);
                        d->Set_Ymid(by_mid);
                        d->Set_Ymax(by_max);
 
                        yl = d->Get_Ylen();
                        yl->Set_length(by_max - by_min);
 
                        d->fix_ymin(TRUE);
                        d->fix_ymid(TRUE);
                        d->fix_ymax(TRUE);
                        d->fix_ylen(TRUE);

                        switch(tp3){
 
                                case XMIN_MIN :
                                	d->Set_Xmin(bx_min);
                                	d->fix_xmin(TRUE);
                                        break;
 
                                case ZMIN_MIN :
                                        d->Set_Zmin(bz_min);
                                        d->fix_zmin(TRUE);
                                        break;
 
                                case XMAX_MAX :
                                	d->Set_Xmax(bx_max);
                                	d->fix_xmax(TRUE);
                                        break;
 
                                case ZMAX_MAX :
                                        d->Set_Zmax(bz_max);
                                        d->fix_zmax(TRUE);
                                        break;
 
                                default :
 
                                post_msg("Error! Choose MIN_MIN or MAX_MAX !");
                                break;
                        }

                                break;
                case ZMIN_MIN :
                case ZMAX_MAX :

                        d->Set_Zmin(bz_min);
                        d->Set_Zmid(bz_mid);
                        d->Set_Zmax(bz_max);
 
                        zl = d->Get_Zlen();
                        zl->Set_length(bz_max - bz_min);
 
                        d->fix_zmin(TRUE);
                        d->fix_zmid(TRUE);
                        d->fix_zmax(TRUE);
                        d->fix_zlen(TRUE);
 
                        switch(tp3){
 
                                case YMIN_MIN :
                                        d->Set_Ymin(by_min);
                                        d->fix_ymin(TRUE);
                                        break;
 
                                case XMIN_MIN :
                                        d->Set_Xmin(bx_min);
                                        d->fix_xmin(TRUE);
                                        break;
 
                                case YMAX_MAX :
                                        d->Set_Ymax(by_max);
                                        d->fix_ymax(TRUE);
                                        break;
 
                                case XMAX_MAX :
                                        d->Set_Xmax(bx_max);
                                        d->fix_xmax(TRUE);
                                        break;
 
                                default :
 
                                post_msg("Error! Choose MIN_MIN or MAX_MAX !");
                                break;
                        }

                                break;
                default :
                                post_msg("Error! Choose MIN_MIN or MAX_MAX !");
                                break;
        }
 

	/*

		!!!!! Here I have ignored tp4 as it has to be
		opposite to tp2 and here user may make some mistakes
		so one way could be to have extensive error checking
		or just neglect it. For the time being 2nd option
		is chosen

	*/

 


}

/*****************************************************************************
*
*       NAME    :       fcm_for_resolve()
*
*       DESCRIPTION :   Assignment of plane values takes place   
*
******************************************************************************/
 
void fcm_for_resolve(int id ,int id1,int tp1)
{

        Block *b = Get_block( currc , id);	 // b is for Base block
        Block *d = Get_block( currc , id1);     // d is for Destination block
 
        int neg = FALSE;
 
        if(id > id1)neg = TRUE; // If Id of base block is greater than
                                // Id of destination then it is negative arc
 

        double bx_min   = b->Get_Xmin();
        double bx_mid   = b->Get_Xmid();
        double bx_max   = b->Get_Xmax();
 
 
        double by_min   = b->Get_Ymin();
        double by_mid   = b->Get_Ymid();
        double by_max   = b->Get_Ymax();
 
        double bz_min   = b->Get_Zmin();
        double bz_mid   = b->Get_Zmid();
        double bz_max   = b->Get_Zmax();
 
        /*
                tp1 is a resting plane. Depending on this following planes
                have to be fixed :
 
                        resting plane for second block
 
		Here MIN_MIN and MAX_MAX options are physically
		unrealizable thus removed
        */
 
        Length* xl;
        Length* yl;
        Length* zl;


        switch(tp1){
 
                case XMIN_MAX :
                                if(neg){
					d->Set_Xmin(bx_max);
                                        d->fix_xmin(TRUE);
                                }
                                else{
                                        d->Set_Xmax(bx_min);
                                        d->fix_xmax(TRUE);
                                }

                        	d->Set_Ymin(by_min);
                        	d->Set_Ymid(by_mid);
                        	d->Set_Ymax(by_max);
 
                        	yl = d->Get_Ylen();
                        	yl->Set_length(by_max - by_min);
 
                        	d->fix_ymin(TRUE);
                        	d->fix_ymid(TRUE);
                        	d->fix_ymax(TRUE);
                        	d->fix_ylen(TRUE);

                        	d->Set_Zmin(bz_min);
                        	d->Set_Zmid(bz_mid);
                        	d->Set_Zmax(bz_max);
 
                        	zl = d->Get_Zlen();
                        	zl->Set_length(bz_max - bz_min);
 
                        	d->fix_zmin(TRUE);
                        	d->fix_zmid(TRUE);
                        	d->fix_zmax(TRUE);
                        	d->fix_zlen(TRUE);

                                break;
                case YMIN_MAX :

                               if(neg){
					d->Set_Ymin(by_max);
                                        d->fix_ymin(TRUE);
                                }
                                else{
                                        d->Set_Ymax(by_min);
                                        d->fix_ymax(TRUE);
                                }

                        	d->Set_Xmin(bx_min);
                        	d->Set_Xmid(bx_mid);
                        	d->Set_Xmax(bx_max);
 
                        	xl = d->Get_Xlen();
                        	xl->Set_length(bx_max - bx_min);
 
                        	d->fix_xmin(TRUE);
                        	d->fix_xmid(TRUE);
                        	d->fix_xmax(TRUE);
                        	d->fix_xlen(TRUE);
 
                                d->Set_Zmin(bz_min);
                                d->Set_Zmid(bz_mid);
                                d->Set_Zmax(bz_max);
 
                                zl = d->Get_Zlen();
                                zl->Set_length(bz_max - bz_min);
 
                                d->fix_zmin(TRUE);
                                d->fix_zmid(TRUE);
                                d->fix_zmax(TRUE);
                                d->fix_zlen(TRUE);

                                break;
                case ZMIN_MAX :

                                if(neg){
					d->Set_Zmin(bz_max);
                                        d->fix_zmin(TRUE);
                                }
                                else{
                                        d->Set_Zmax(bz_min);
                                        d->fix_zmax(TRUE);
                                }
 
                                d->Set_Ymin(by_min);
                                d->Set_Ymid(by_mid);
                                d->Set_Ymax(by_max);
 
                                yl = d->Get_Ylen();
                                yl->Set_length(by_max - by_min);
 
                                d->fix_ymin(TRUE);
                                d->fix_ymid(TRUE);
                                d->fix_ymax(TRUE);
                                d->fix_ylen(TRUE);

                                d->Set_Xmin(bx_min);
                                d->Set_Xmid(bx_mid);
                                d->Set_Xmax(bx_max);
 
                                xl = d->Get_Xlen();
                                xl->Set_length(bx_max - bx_min);
 
                                d->fix_xmin(TRUE);
                                d->fix_xmid(TRUE);
                                d->fix_xmax(TRUE);
                                d->fix_xlen(TRUE);

                                break;
 
                case XMAX_MIN :

                                if(neg){
					d->Set_Xmax(bx_min);
                                        d->fix_xmax(TRUE);
                                }
                                else{
                                        d->Set_Xmin(bx_max);
                                        d->fix_xmin(TRUE);
                                }

                                d->Set_Ymin(by_min);
                                d->Set_Ymid(by_mid);
                                d->Set_Ymax(by_max);
 
                                yl = d->Get_Ylen();
                                yl->Set_length(by_max - by_min);
 
                                d->fix_ymin(TRUE);
                                d->fix_ymid(TRUE);
                                d->fix_ymax(TRUE);
                                d->fix_ylen(TRUE);
 
                                d->Set_Zmin(bz_min);
                                d->Set_Zmid(bz_mid);
                                d->Set_Zmax(bz_max);
 
                                zl = d->Get_Zlen();
                                zl->Set_length(bz_max - bz_min);
 
                                d->fix_zmin(TRUE);
                                d->fix_zmid(TRUE);
                                d->fix_zmax(TRUE);
                                d->fix_zlen(TRUE);
 
                                break;
                case YMAX_MIN :

                                if(neg){
					d->Set_Ymax(by_min);
                                        d->fix_ymax(TRUE);
                                }
                                else{
                                        d->Set_Ymin(by_max);
                                        d->fix_ymin(TRUE);
                                }
                                d->Set_Xmid(bx_mid);

                                d->Set_Xmin(bx_min);
                                d->Set_Xmid(bx_mid);
                                d->Set_Xmax(bx_max);
 
                                xl = d->Get_Xlen();
                                xl->Set_length(bx_max - bx_min);
 
                                d->fix_xmin(TRUE);
                                d->fix_xmid(TRUE);
                                d->fix_xmax(TRUE);
                                d->fix_xlen(TRUE);
 
                                d->Set_Zmin(bz_min);
                                d->Set_Zmid(bz_mid);
                                d->Set_Zmax(bz_max);
 
                                zl = d->Get_Zlen();
                                zl->Set_length(bz_max - bz_min);
 
                                d->fix_zmin(TRUE);
                                d->fix_zmid(TRUE);
                                d->fix_zmax(TRUE);
                                d->fix_zlen(TRUE);
 
                                break;
                case ZMAX_MIN :

                                if(neg){
					d->Set_Zmax(bz_min);
                                        d->fix_zmax(TRUE);
                                }
                                else{
                                        d->Set_Zmin(bz_max);
                                        d->fix_zmin(TRUE);
                                }

                                d->Set_Ymin(by_min);
                                d->Set_Ymid(by_mid);
                                d->Set_Ymax(by_max);
 
                                yl = d->Get_Ylen();
                                yl->Set_length(by_max - by_min);
 
                                d->fix_ymin(TRUE);
                                d->fix_ymid(TRUE);
                                d->fix_ymax(TRUE);
                                d->fix_ylen(TRUE);
 
                                d->Set_Xmin(bx_min);
                                d->Set_Xmid(bx_mid);
                                d->Set_Xmax(bx_max);
 
                                xl = d->Get_Xlen();
                                xl->Set_length(bx_max - bx_min);
 
                                d->fix_xmin(TRUE);
                                d->fix_xmid(TRUE);
                                d->fix_xmax(TRUE);
                                d->fix_xlen(TRUE);
 
                                break;

		default 	:

				post_msg("Error ! No MIN_MIN and MAX_MAX ");
				break;
        }

}

/*****************************************************************************
*
*       NAME    :       spm_for_resolve()
*
*       DESCRIPTION :   Assignment of plane values takes place   
*
******************************************************************************/
 
void spm_for_resolve(int id ,int id1 ,int tp1)
{

        Block *b = Get_block( currc , id);	 // b is for Base block
        Block *d = Get_block( currc , id1);     // d is for Destination block
 
        int neg = FALSE;
 
        if(id > id1)neg = TRUE; // If Id of base block is greater than
                                // Id of destination then it is negative arc
 

        double bx_min   = b->Get_Xmin();
        double bx_mid   = b->Get_Xmid();
        double bx_max   = b->Get_Xmax();
 
 
        double by_min   = b->Get_Ymin();
        double by_mid   = b->Get_Ymid();
        double by_max   = b->Get_Ymax();
 
        double bz_min   = b->Get_Zmin();
        double bz_mid   = b->Get_Zmid();
        double bz_max   = b->Get_Zmax();
 

        switch(tp1){
 
                case XMIN_MIN :
                                d->Set_Xmin(bx_min);
                                d->fix_xmin(TRUE);
                                break;
                case XMIN_MAX :
                                if(neg){
					d->Set_Xmin(bx_max);
                                        d->fix_xmin(TRUE);
                                }
                                else{
                                        d->Set_Xmax(bx_min);
                                        d->fix_xmax(TRUE);
                                }
 
                                break;
                case YMIN_MIN :
                                d->Set_Ymin(by_min);
                                d->fix_ymin(TRUE);
                                break;
                case YMIN_MAX :
                                if(neg){
					d->Set_Ymin(by_max);
                                        d->fix_ymin(TRUE);
                                }
                                else{
                                        d->Set_Ymax(by_min);
                                        d->fix_ymax(TRUE);
                                }
                                break;
                case ZMIN_MIN :
                                d->Set_Zmin(bz_min);
                                d->fix_zmin(TRUE);
                                break;
                case ZMIN_MAX :
                                if(neg){
					d->Set_Zmin(bz_max);
                                        d->fix_zmin(TRUE);
                                }
                                else{
                                        d->Set_Zmax(bz_min);
                                        d->fix_zmax(TRUE);
                                }
 
                                break;
 
                case XMAX_MIN :
                                if(neg){
					d->Set_Xmax(bx_min);
                                        d->fix_xmax(TRUE);
                                }
                                else{
                                        d->Set_Xmin(bx_max);
                                        d->fix_xmin(TRUE);
                                }
                                break;
                case XMAX_MAX :
                                d->Set_Xmax(bx_max);
                                d->fix_xmax(TRUE);
                                break;
                case YMAX_MIN :
                                if(neg){
					d->Set_Ymax(by_min);
                                        d->fix_ymax(TRUE);
                                }
                                else{
                                        d->Set_Ymin(by_max);
                                        d->fix_ymin(TRUE);
                                }
                                break;
                case YMAX_MAX :
                                d->Set_Ymax(by_max);
                                d->fix_ymax(TRUE);
                                break;
                case ZMAX_MIN :
                                if(neg){
					d->Set_Zmax(bz_min);
                                        d->fix_zmax(TRUE);
                                }
                                else{
                                        d->Set_Zmin(bz_max);
                                        d->fix_zmin(TRUE);
                                }
                                break;
                case ZMAX_MAX :
                                d->Set_Zmax(bz_max);
                                d->fix_zmax(TRUE);
                                break;
        }

}



 

 
