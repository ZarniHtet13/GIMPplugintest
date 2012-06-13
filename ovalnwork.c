/*
Plug-in Description : Building Rectangles and Ellipses
Author : Based on the tutorial at gimp-plug-in development
Modified/Documented by: Zarni Htet@the RAMS 06/13/2012
Further documentation and modification : 
*/


#include <libgimp/gimp.h>
#include <libgimp/gimpui.h>


static void query (void);
static void run (const gchar *name,
                   gint nparams,
                   const GimpParam *param,
                   gint *nreturn_vals,
                   GimpParam **return_vals);
static void modos (GimpDrawable *drawable, gint image) ;
GimpPlugInInfo PLUG_IN_INFO =
{
  NULL,
  NULL,
  query,
  run
};

MAIN()

static void
query (void)
{
  static GimpParamDef args[] =
  {
    {
      GIMP_PDB_INT32,
      "run-mode",
      "Run mode"
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

  gimp_install_procedure (
    "plug-in-oval",
    "Lovely Oval!",
    "Displays \"An Oval \" in the pane",
    "the RAMS",
    "Copyright the RAMS",
    "2012",
    "_Oval",
    "RGB*, GRAY*",
    GIMP_PLUGIN,
    G_N_ELEMENTS (args), 0,
    args, NULL);

  gimp_plugin_menu_register ("plug-in-oval",
                             "<Image>/Filters/Misc");
}

static void
run (const gchar *name,
     gint nparams,
     const GimpParam *param,
     gint *nreturn_vals,
     GimpParam **return_vals)
{
  static GimpParam values[1];
  GimpPDBStatusType status = GIMP_PDB_SUCCESS;
  GimpRunMode run_mode;

  GimpDrawable *drawable;
  gint image;

  /* Setting mandatory output values */
  *nreturn_vals = 1;
  *return_vals = values;

  values[0].type = GIMP_PDB_STATUS;
  values[0].data.d_status = status;

  /* Getting run_mode - we won't display a dialog if
* we are in NONINTERACTIVE mode */
  run_mode = param[0].data.d_int32;

  // we do not know why we would need this since the tutorial does not have it and Chikah has it.
  // values[1].type = GIMP_PDB_IMAGE;
  //values[1].data.d_image = image;

  //we will get the specified drawable
  drawable = gimp_drawable_get(param[2].data.d_drawable);
   image= param[1].data.d_image;
   
  //dumping changes made in PDB, into the GIMP core

   modos (drawable, image);
  gimp_displays_flush();
  gimp_drawable_detach(drawable);
  
 
}

static void modos (GimpDrawable *drawable ,gint image)
{
  gint width, height;

  /* gint32
     typedef signed int gint32;
A signed integer guaranteed to be 32 bits on all platforms. Values of this type can range from -2,147,483,648 to 2,147,483,647.
guint32
typedef unsigned int guint32;
An unsigned integer guaranteed to be 32 bits on all platforms. Values of this type can range from 0 to 4,294,967,295.
  */

  gint32 selection ; 

  // getting the image size
  width = gimp_image_width(image);
#include <gtk/gtk.h>


// structure to store the values of the rectangle figure that would be interfaced with the GUI
typedef struct
{
  gfloat xposition;
  gfloat yposition;
  gfloat width;
  gfloat height;
  gint32 operation;
  gint32 feather;
  gfloat fr;
}MyRect;

// default values for the rectangle option
static MyRect zars =
  {
    40,   // x position
    30,   // y position
    200,  // width
    150,  // height
    0,    // operation (which is just adding)
    30,   // feather (that blurry effect at the edges)
    5,    // feather radius
  };


static void query (void);
static void run (const gchar *name,
                   gint nparams,
                   const GimpParam *param,
                   gint *nreturn_vals,
                   GimpParam **return_vals);
static void modos (GimpDrawable *drawable, gint image) ;
GimpPlugInInfo PLUG_IN_INFO =
{
  NULL,
  NULL,
  query,
  run
};

MAIN()

static void
query (void)
{
  static GimpParamDef args[] =
  {
    {
      GIMP_PDB_INT32,
      "run-mode",
      "Run mode"
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

  gimp_install_procedure (
    "plug-in-oval",
    "Lovely Oval!",
    "Displays \"An Oval \" in the pane",
    "the RAMS",
    "Copyright the RAMS",
    "2012",
    "_Oval",
    "RGB*, GRAY*",
    GIMP_PLUGIN,
    G_N_ELEMENTS (args), 0,
    args, NULL);

  gimp_plugin_menu_register ("plug-in-oval",
                             "<Image>/Filters/Misc");
}

static void
run (const gchar *name,
     gint nparams,
     const GimpParam *param,
     gint *nreturn_vals,
     GimpParam **return_vals)
{
  static GimpParam values[1];
  GimpPDBStatusType status = GIMP_PDB_SUCCESS;
  GimpRunMode run_mode;

  GimpDrawable *drawable;
  gint image;

  /* Setting mandatory output values */
  *nreturn_vals = 1;
  *return_vals = values;

  values[0].type = GIMP_PDB_STATUS;
  values[0].data.d_status = status;

  /* Getting run_mode - we won't display a dialog if
* we are in NONINTERACTIVE mode */
  run_mode = param[0].data.d_int32;

  //Get the specified drawable


  // we do not know why we would need this since the tutorial does not have it and Chikah has it.
  // values[1].type = GIMP_PDB_IMAGE;
  //values[1].data.d_image = image;

  //we will get the specified drawable
  drawable = gimp_drawable_get(param[2].data.d_drawable);
   image= param[1].data.d_image;

   /* switch (run_mode)
    {
    case GIMP_RUN_INTERACTIVE:
      // Get options last values if needed 
      gimp_get_data ("plug-in-frame", &zars);

      // Display the dialog 
      if (! frame_dialog (drawable))
	return;
      break;
    case GIMP_RUN_NONINTERACTIVE:
      if (nparams != 4)
	status = GIMP_PDB_CALLING_ERROR;
      if (status == GIMP_PDB_SUCCESS)
	vals.offset = param[3].data.d_int32;
      break;

    case GIMP_RUN_WITH_LAST_VALS:
      //  Get options last values if needed  
      gimp_get_data ("plug-in-frame", &zars);
      break;

    default:
      break;
      }*/

   
  //dumping changes made in PDB, into the GIMP core

   modos (drawable, image);
   // frame_dialog (drawable);
  gimp_displays_flush();
  gimp_drawable_detach(drawable);
  
 
}

static void modos (GimpDrawable *drawable ,gint image)
{
  gint width, height;

  /* gint32
     typedef signed int gint32;
A signed integer guaranteed to be 32 bits on all platforms. Values of this type can range from -2,147,483,648 to 2,147,483,647.
guint32
typedef unsigned int guint32;
An unsigned integer guaranteed to be 32 bits on all platforms. Values of this type can range from 0 to 4,294,967,295.
  */

  gint32 selection ; 

  // getting the image size
  width = gimp_image_width(image);
  height = gimp_image_height(image);

  // save the selection to load it up into a channel (is it about doing a shadown copy?
 
  //FLAG: We do not need this. When would we need it?
  // selection = gimp_selection_save(image);
  

  // now, we will select a rectangle
  // gimp_rect_select(image, width/2, height/2, width/3, height/3, 0, 10, 20);
  gimp_rect_select(image, zars.xposition, zars.yposition, zars.width, zars.height, zars.operation,zars.feather, zars.fr);

  // FLAG! edit_bucket fill has some parameter error. Not enough documentation so far.
 // gimp_edit_bucket_fill(image, 1, 1, 20, 20, TRUE, NULL, NULL);
 
 // gimp_ellipse_select(image, width/6, height/6, width/4, height/4, 0, TRUE, 10, 20);
  
  gimp_edit_fill (drawable->drawable_id,4);
  // gimp_selection_load(selection); // we probably do not need this.

}

/*static void hello (GtkWidget *widget, gpointer data)
{
 
  g_print ("Hello World\n") ;

  }*/

   /*static gboolean
frame_dialog (GimpDrawable *drawable)
{
  GtkWidget *dialog;
  GtkWidget *main_vbox;
  GtkWidget *main_hbox;
  GtkWidget *frame;
  GtkWidget *frame_label;
  GtkWidget *alignment;
  GtkWidget *spinbutton;
  GtkWidget  *spinbutton2;
  GtkWidget  *text;
  GtkObject *spinbutton_adj;
  GtkWidget *border_label;
  gboolean   run;

  gimp_ui_init ("frame", FALSE);

  dialog = gimp_dialog_new ("My frame", "myframe",
			    NULL, 0,
			    gimp_standard_help_func, "plug-in-frame",

			    GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
			    GTK_STOCK_OK,     GTK_RESPONSE_OK,

			    NULL);

  main_vbox = gtk_vbox_new (FALSE, 6);
  gtk_container_add (GTK_CONTAINER (GTK_DIALOG (dialog)->vbox), main_vbox);
  gtk_widget_show (main_vbox);

  frame = gtk_frame_new (NULL);
  gtk_widget_show (frame);
  gtk_box_pack_start (GTK_BOX (main_vbox), frame, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (frame), 6);

  alignment = gtk_alignment_new (0.5, 0.5, 1, 1);
  gtk_widget_show (alignment);
  gtk_container_add (GTK_CONTAINER (frame), alignment);
  gtk_alignment_set_padding (GTK_ALIGNMENT (alignment), 6, 6, 6, 6);

  main_hbox = gtk_hbox_new (FALSE, 0);
  gtk_widget_show (main_hbox);
  gtk_container_add (GTK_CONTAINER (alignment), main_hbox);

  frame_label = gtk_label_new_with_mnemonic ("_Offset-Weather");
  gtk_widget_show (frame_label);
  gtk_box_pack_start (GTK_BOX (main_hbox), frame_label, FALSE, FALSE, 6);
  gtk_label_set_justify (GTK_LABEL (frame_label), GTK_JUSTIFY_RIGHT);

  spinbutton_adj = gtk_adjustment_new (0, 1, 100, 1, 5, 5);
  spinbutton = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton_adj), 1, 0);
  gtk_widget_show (spinbutton);
  gtk_box_pack_start (GTK_BOX (main_hbox), spinbutton, FALSE, FALSE, 6);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (spinbutton), TRUE);


  border_label = gtk_label_new ("Modify frame");
  gtk_widget_show (border_label);
  gtk_frame_set_label_widget (GTK_FRAME (frame), frame_label);
  gtk_label_set_use_markup (GTK_LABEL (frame_label), TRUE);

  g_signal_connect (spinbutton_adj, "value_changed",
		    G_CALLBACK (gimp_int_adjustment_update),
		    &vals.offset);

  spinbutton_adj = gtk_adjustment_new (0, 1, 255, 1, 5, 5);
  spinbutton2 = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton_adj), 1, 0);
  gtk_widget_show (spinbutton2);
  gtk_box_pack_start (GTK_BOX (main_hbox), spinbutton2, FALSE, FALSE, 6);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (spinbutton2), TRUE);

  g_signal_connect (spinbutton_adj, "value_changed",
		    G_CALLBACK (gimp_int_adjustment_update),
		    &vals.weather);

  gtk_widget_show (dialog);

  run = (gimp_dialog_run (GIMP_DIALOG (dialog)) == GTK_RESPONSE_OK);

  gtk_widget_destroy (dialog);

  return run;
  }*/
