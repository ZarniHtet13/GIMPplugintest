#include <libgimp/gimp.h>

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
  height = gimp_image_height(image);

  // save the selection to load it up into a channel (is it about doing a shadown copy?
 
  //FLAG: We do not need this. When would we need it?
  // selection = gimp_selection_save(image);
  

  // now, we will select a rectangle
  gimp_rect_select(image, width/2, height/2, width/3, height/3, 0, 0, 0);
  gimp_edit_fill (drawable->drawable_id, 0);
  // gimp_selection_load(selection); // we probably do not need this.
  
  



}


