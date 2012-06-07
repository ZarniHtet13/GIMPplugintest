/*
Description: Simple Hello World Plug-in
Author : Dave Neary from GIMP developers
Documented : Zarni Htet @ The RAMS (06/08/2012)
Documentation Edited :             (06/08/2012)
*/

/* The architecture : The Plug-in will communicate via PDB (Procedural database (PDB). Functions that we wish to utilize must be exposed to PDB and libgimp so that they can be called as a normal one. */

/* Neessary tools: gimptool-2.0 for installing it as a plug-in. */

// Four basic plug-in elements init, quit, query, run.


#include <libgimp/gimp.h>

// query function called each time the plug-in changes
static void query (void);
// run plug-in is the heart of the plug-in program
// the parameters are name, inputparameters and a pointer to output parameters.
static void run   (const gchar      *name,
                   gint              nparams,
                   const GimpParam  *param,
                   gint             *nreturn_vals,
                   GimpParam       **return_vals);


// Null Null corresponds to the two of the gimptool function that is option
// which are init and close which are for the beginning and ending of the gimp-plug-in
GimpPlugInInfo PLUG_IN_INFO =
{
  NULL,
  NULL,
  query,
  run
};

MAIN()

// this is the query function obviously
static void
query (void)
{

// contains three things - the parameter type, its name, and a string describing the parameter

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

//the install procedure would have the procedure name, a description of what it is, the location of the plug-in, the type of images the plug-in would handle, the input and output parameters of the plug-in.


  gimp_install_procedure (
    "plug-in-hello",
    "Hello, world!",
    "Displays \"Hello, world!\" in a dialog",
    "David Neary",
    "Copyright David Neary",
    "2004",
    "_Hello world...",
    "RGB*, GRAY*",    // image type which would be RGB, RGBA, GRAY image types
    GIMP_PLUGIN,      // This is declaring that the procedure should not be executed in the                      // GIMP-core

    G_N_ELEMENTS (args), 0,
    args, NULL);

  gimp_plugin_menu_register ("plug-in-hello",
                             "<Image>/Filters/Misc");
}




// this is the run function
// there are three ways to run the GIMP-plug-in
// You can do it through GIMP_RUN_INTERACTIVE or GIMP_RUN_NONINTERACTIVE or GIMP_RUN_WITH_LAST_VALS
// Only the GIMP_RUN_INTERACTIVE can allow you to run the plug-in from an options dialog
// The other ones are directly from "input parameters or from memory".
// we will need to read about GTK+ to be able to implement this plug-in business.

// why do we have to set mandatory outputs? 
// we are in INTERACTIVE MODE : How and where we set it up?

static void
run (const gchar      *name,
     gint              nparams,
     const GimpParam  *param,
     gint             *nreturn_vals,
     GimpParam       **return_vals)


{
  static GimpParam  values[1];
  GimpPDBStatusType status = GIMP_PDB_SUCCESS;
  GimpRunMode       run_mode;

  /* Setting mandatory output values */
  *nreturn_vals = 1;
  *return_vals  = values;

  values[0].type = GIMP_PDB_STATUS;
  values[0].data.d_status = status;

  /* Getting run_mode - we won't display a dialog if 
   * we are in NONINTERACTIVE mode */
  run_mode = param[0].data.d_int32;

  if (run_mode != GIMP_RUN_NONINTERACTIVE)
    g_message("We are the RAMS!\n");
}

