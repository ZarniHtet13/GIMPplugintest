#include <libgimp/gimp.h>
#include <libgimp/gimpui.h>

typedef struct
{
  gint width;

} MyOval;

static void query (void);
static void run (const gchar *name,
                   gint nparams,
                   const GimpParam *param,
                   gint *nreturn_vals,
                   GimpParam **return_vals);
static void modos (GimpDrawable *drawable, gint image) ;
static gboolean oval_dialog (GimpDrawable *drawable);

static MyOval vals =
  {
    50,  // width 
  };

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
  static GimpParam values[2];
  GimpPDBStatusType status = GIMP_PDB_SUCCESS;
  GimpRunMode run_mode;

  GimpDrawable *drawable;
  gint image;

  /* Setting mandatory output values */
  *nreturn_vals = 2;
  *return_vals = values;

  values[0].type = GIMP_PDB_STATUS;
  values[0].data.d_status = status;

  /* Getting run_mode - we won't display a dialog if
* we are in NONINTERACTIVE mode */
  run_mode = param[0].data.d_int32;


  //we will get the specified drawable
  drawable = gimp_drawable_get(param[2].data.d_drawable);
   image= param[1].data.d_image;

switch (run_mode)
    {
    case GIMP_RUN_INTERACTIVE:
      // Get options last values if needed
      gimp_get_data ("plug-in-oval", &vals);

      // Display the dialog
      if (! oval_dialog (drawable))
	return;
      break;

    case GIMP_RUN_NONINTERACTIVE:
      if (nparams != 4)
	status = GIMP_PDB_CALLING_ERROR;
      if (status == GIMP_PDB_SUCCESS)
	vals.width = param[3].data.d_int32;
      break;

    case GIMP_RUN_WITH_LAST_VALS:
      //  Get options last values if needed
      gimp_get_data ("plug-in-oval", &vals);
      break;

    default:
      break;
    }
   
  //dumping changes made in PDB, into the GIMP core

  modos (drawable, image);
  gimp_displays_flush();
  gimp_drawable_detach(drawable);
  
 if (run_mode == GIMP_RUN_INTERACTIVE)
    gimp_set_data ("plug-in-oval", &vals, sizeof (MyOval));

 return;
}

static void modos (GimpDrawable *drawable ,gint image)
{
  gint width, height;
  gint32 selection ; //what the hell is gint32 fo now?


  // getting the image size
  width = gimp_image_width(image);
  height = gimp_image_height(image);

  // save the selection to load it up into a channel (is it about doing a shadown copy?

  selection = gimp_selection_save(image);
  

  // now, we will select a rectangle
  gimp_rect_select(image, vals.width, vals.width, width/3, height/3, 0, 0, 0);
  gimp_edit_fill (drawable->drawable_id, 4);
  gimp_selection_load(selection);
  
 }

static gboolean
oval_dialog (GimpDrawable *drawable)
{
  GtkWidget *dialog;
  GtkWidget *main_vbox;
  GtkWidget *main_hbox;
  GtkWidget *frame;
  GtkWidget *width_label;
  GtkWidget *alignment;
  GtkWidget *spinbutton;
  GtkObject *spinbutton_adj;
  GtkWidget *frame_label;
  gboolean   run;



gimp_ui_init ("oval", FALSE);

  dialog = gimp_dialog_new ("My Oval", "myoval",
			    NULL, 0,
			    gimp_standard_help_func, "plug-in-oval",

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

  width_label = gtk_label_new_with_mnemonic ("Width/Length:");
  gtk_widget_show (width_label);
  gtk_box_pack_start (GTK_BOX (main_hbox), width_label, FALSE, FALSE, 6);
  gtk_label_set_justify (GTK_LABEL (width_label), GTK_JUSTIFY_RIGHT);

  spinbutton_adj = gtk_adjustment_new (3, 1, 16, 1, 5, 5);
  spinbutton = gtk_spin_button_new (GTK_ADJUSTMENT (spinbutton_adj), 1, 0);
  gtk_widget_show (spinbutton);
  gtk_box_pack_start (GTK_BOX (main_hbox), spinbutton, FALSE, FALSE, 6);
  gtk_spin_button_set_numeric (GTK_SPIN_BUTTON (spinbutton), TRUE);

  frame_label = gtk_label_new ("<b>Modify oval</b>");
  gtk_widget_show (frame_label);
  gtk_frame_set_label_widget (GTK_FRAME (frame), frame_label);
  gtk_label_set_use_markup (GTK_LABEL (frame_label), TRUE);

  g_signal_connect (spinbutton_adj, "value_changed",
                    G_CALLBACK (gimp_int_adjustment_update),
                    &vals.width);
  gtk_widget_show (dialog);

  run = (gimp_dialog_run (GIMP_DIALOG (dialog)) == GTK_RESPONSE_OK);

  gtk_widget_destroy (dialog);

  return run;

}
