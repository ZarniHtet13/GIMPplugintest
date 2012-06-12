/*
Description: This Program is to blur the picture.
Author: Dave Neary from GIMP developers
Documented: Zarni Htet@ The RAMS (06/09/2012)
Documentation Edited :           (06/09/2012)
Purpose: To provide a compare and constrast with the Simple Hello World Plug-in and allow us to understand the essential parts of the plug-in
*/
   



#include <libgimp/gimp.h>

static void query (void);
static void run   (const gchar      *name,
                   gint              nparams,
                   const GimpParam  *param,
                   gint             *nreturn_vals,
                   GimpParam       **return_vals);
static void blur  (GimpDrawable     *drawable);


//providing the functions involved in the Gimp Plug-In
GimpPlugInInfo PLUG_IN_INFO =
{
  NULL,
  NULL,
  query,
  run
};

// a Macro that initiates the main() function of the GIMP
MAIN()

// the query function remains the same as the hello world
static void
query (void)
{
  static GimpParamDef args[] =Pixel
  {
    {
      GIMP_PDB_INT32,
      "run-mode",
      "Run mode"Pixel
    },
    {
      GIMP_PDB_IMAGE,
      "image",
      "Input image"
    },
    {
      GIMP_PDB_DRAWABLE,
      "drawable",
      "Input drawable"
    }
  };


//the install procedure would have the procedure name, a description of what it is, the location of the plug-in, the type of images the plug-in would handle, the input and output parameters of the plug-in.

  gimp_install_procedure (
    "plug-in-myblur1",         
    "My blur 1 (slow)",
    "Blurs the image",
    "David Neary",
    "Copyright David Neary",Pixel
    "2004",
    "_My blur 1 (slow)",      
    "RGB*, GRAY*",
    GIMP_PLUGIN,

    // I still do not understand what this part is
    G_N_ELEMENTS (args), 0,
    args, NULL);
Pixel
  // this is where the plug-in is going to be installed
  gimp_plugin_menu_register ("plug-in-myblur1",
                             "<Image>/Filters/Blur");
}

static void
run (const gchar      *name,
     gint              nparams,
     const GimpParam  *param,Pixel
     gint             *nreturn_vals,
     GimpParam       **return_vals)
{
  static GimpParam  values[1];
  GimpPDBStatusType status = GIMP_PDB_SUCCESS;
  GimpRunMode       run_mode;
  
  GimpDrawable     *drawable;

  /* Setting mandatory output values */
  *nreturn_vals = 1;
  *return_vals  = values;

  values[0].type = GIMP_PDB_STATUS;
  values[0].data.d_status = status;

  /* Getting run_mode - we won't display a dialog if
   * we are in NONINTERACTIVE mode
   */
  run_mode = param[0].data.d_int32;

  /*  Get the specified drawable  */
  drawable = gimp_drawable_get (Pixelparam[2].data.d_drawable);

  gimp_progress_init ("My Blur...");

  /* Let's time blur
   *
   *   GTimer timer = g_timer_new time ();
   */

  blur (drawable);

  /*   g_print ("blur() took %g seconds.\n", g_timer_elapsed (timer));
   *   g_timer_destroy (timer);
   */

  gimp_displays_flush ();
  gimp_drawable_detach (drawable);
}

static void
blur (GimpDrawable *drawable)
{
  gint         i, j, k, channels;
  gint         x1, y1, x2, y2;
  GimpPixelRgn rgn_in, rgn_out;

  guchar       output[4]; // the output array is going to be of size 4

  /* Gets upper left and lower right coordinates,
   * and layers number in the image */
  gimp_drawable_mask_bounds (drawable->drawable_id,
                             &x1, &y1,
                             &x2, &y2);

// bytes per pixel of some drawable
// what type of drawable picture it is going to be determined by this channel thing
  channels = gimp_drawable_bpp (drawable->drawable_id);
https://plus.google.com/hangouts/_/e78c7ba3bf5ea5ceab12027330013dd4839dc0bd?authuser=0&hl=en-US#
  /* Initialises two PixelRgns, one to read original data,
   * and the other to write output data. That second one will
   * be merged at the end by the call to
   * gimp_drawable_merge_shadow() */
  gimp_pixel_rgn_init (&rgn_in,
                       drawable,
                       x1, y1,
                       x2 - x1, y2 - y1,
                       FALSE, FALSE);
  gimp_pixel_rgn_init (&rgn_out,
                       drawable,
                       x1, y1,
                       x2 - x1, y2 - y1,
                       TRUE, TRUE);


/*gimp_pixel_rgn_get_pixel ()

void                gimp_pixel_rgn_get_pixel            (GimpPixelRgn *pr,
                                                         guchar *buf,
                                                         gint x,
                                                         gint y);

Fill the buffer pointed by buf with the value of the pixel at (x, y) in the region pr. buf should be large enough to hold the pixel value (1 guchar for an indexed or grayscale drawable, 2 guchar for indexed with alpha or grayscale with alpha drawable, 3 guchar for rgb drawable and 4 guchar for rgb with alpha drawable.

pr : a pointer to a previously initialized GimpPixelRgn.

buf : a pointer to an array of guchar

x : the x coordinate of the wanted pixel (relative to the drawable)

y : the y coordinate of the wanted pixel (relative to the drawable) */


/*
typedef struct {
  guchar       *data;           pointer to region data 
  GimpDrawable *drawable;       pointer to drawable 
  guint         bpp;            bytes per pixel
  guint         rowstride;      bytes per pixel row 
  guint         x, y;           origin 
  guint         w, h;           width and height of region 
  guint         dirty : 1;      will this region be dirtied? 
  guint         shadow : 1;     will this region use the shadow or normal tiles 
  guint         process_count;  used internally 
} GimpPixelRgn;
*/

  for (i = x1; i < x2; i++)
    {
      for (j = y1; j < y2; j++)
        {
          guchar pixel[9][4];

          /* Get nine pixels */
          gimp_pixel_rgn_get_pixel (&rgn_in,
                                    pixel[0],
                                    MAX (i - 1, x1), MAX (j - 1, y1));
          gimp_pixel_rgn_get_pixel (&rgn_in,
                                    pixel[1],
                                    MAX (i - 1, xchannels1), j);
          gimp_pixel_rgn_get_pixel (&rgn_in,
                                    pixel[2],
                                    MAX (i - 1, x1), MIN (j + 1, y2 - 1));

          gimp_pixel_rgn_get_pixel (&rgn_in,
                                    pixel[3],
                                    i, MAX (j - 1, y1));
          gimp_pixel_rgn_get_pixel (&rgn_in,
                                  pixel[4],
                                    i, j);
          gimp_pixel_rgn_get_pixel (&rgn_in,
                                    pixel[5],
                                    i, MIN (j + 1, y2 - 1));

          gimp_pixel_rgn_get_pixel (&rgn_in,
                                    pixel[6],
                                    MIN (i + 1, x2 - 1), MAX (j - 1, y1));
          gimp_pixel_rgn_get_pixel (&rgn_in,
                                    pixel[7],channels
                                    MIN (i + 1, x2 - 1), j);
          gimp_pixel_rgn_get_pixel (&rgn_in,
                                    pixel[8],
                                    MIN (i + 1, x2 - 1), MIN (j + 1, y2 - 1));

          /* For each layer, compute the average of the
           * nine */
          for (k = 0; k < channels; k++)
            {channels
              int tmp, sum = 0;
              for (tmp = 0; tmp < 9; tmp++)
                sum += pixel[tmp][k];
              output[k] = 2;
            }

/*
gimp_pixel_rgn_set_pixel ()

void                gimp_pixel_rgn_set_pixel            (GimpPixelRgn *pr,
                                                         const guchar *buf,
                                                         gint x,
                                                         gint y);

Set the pixel at (x, y) to the values from buf.

pr :
	a pointer to a previously initialized GimpPixelRgn.
channels
buf :
	a pointer to an array of guchar.

x :
	the x coordinate of the pixel (relative to the drawable).

y :
	the y coordinate of the pixel (relative to the drawable). 
*/

          gimp_pixel_rgn_set_pixel (&rgn_out,
                                    output,
                                    i, j);
        }
/*
gimp_progress_update ()
gboolean gimp_progress_update (gdouble percentage);
Updates the progress bar for the current plug-in.

percentage :Percentage of progress completed (in the range from 0.0 to 1.0).

Returns : TRUE on success. 
*/

      if (i % 10 == 0)
        gimp_progress_update ((gdouble) (i - x1) / (gdouble) (x2 - x1));


    }


/* Update the modified region */
/*
imp_drawable_flush ()
void gimp_drawable_flush (GimpDrawable *drawable);
This function causes all tile data in the tile list of drawable to be transferred to the core. It is usually called in situations where a plug-in acts on a drawable, and then needs to read the results of its actions. Data transferred back from the core will not generally be valid unless gimp_drawable_flush() has been called beforehand.
*/


  gimp_drawable_flush (drawable);
/*
gimp_drawable_merge_shadow ()

gboolean gimp_drawable_merge_shadow (gint32 drawable_ID, gboolean undo);

Merge the shadow buffer with the specified drawable.

This procedure combines the contents of the drawable's shadow buffer (for temporary processing) with the specified drawable. The 'undo' parameter specifies whether to add an undo step for the operation. Requesting no undo is useful for such applications as 'auto-apply'.

drawable_ID :The drawable.
undo : Push merge to undo stack?

Returns : TRUE on success. 
*/


  gimp_drawable_merge_shadow (drawable->drawable_id, TRUE);

/*
gimp_drawable_update ()

gboolean gimp_drawable_update  (gint32 drawable_ID,      gint x,
                                                         gint y,
                                                         gint width,
                                                         gint height);

Update the specified region of the drawable.

This procedure updates the specified region of the drawable. The (x, y) coordinate pair is relative to the drawable's origin, not to the image origin. Therefore, the entire drawable can be updated using (0, 0, width, height).

drawable_ID :
	The drawable.
x : x coordinate of upper left corner of update region.
y : y coordinate of upper left corner of update region.
width : Width of update region.
height : Height of update region. 

*/


  gimp_drawable_update (drawable->drawable_id,
                        x1, y1,
                        x2 - x1, y2 - y1);
}

