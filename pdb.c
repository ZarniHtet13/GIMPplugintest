#include <libgimp/gimp.h>
#include <stdio.h>

static void query (void);

static void run    (const gchar *name,
                   gint nparams,
                   const GimpParam *param,
                   gint *nreturn_vals,
                   GimpParam **return_vals);
static void modos (GimpDrawable *drawable, gint image) ;

static gboolean oval_dialog (GimpDrawable *drawable);

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
    "plug-in-pdb",
    "Lovely Oval!",
    "Displays \"The List of PDBs",
    "the RAMS",
    "Copyright the RAMS",
    "2012",
    "PDB",
    "RGB*, GRAY*",
    GIMP_PLUGIN,
    G_N_ELEMENTS (args), 0,
    args, NULL);

  gimp_plugin_menu_register ("plug-in-pdb",
                             "<Image>/Filters/Misc");
}

static void
run (const gchar *name,
     gint nparams,
     const GimpParam *param,
     gint *nreturn_vals ,
     GimpParam **return_vals)
{
  static GimpParam values[1];
  GimpPDBStatusType status = GIMP_PDB_SUCCESS;
  GimpRunMode run_mode;
    
  // gboolean gimp_procedural_db_dump (const gchar *filename);
 gboolean gimp_procedural_db_query();
  //gint *num_matches ;
  //num_matches = 1;
  //gchar ***procedure_names;
 

  /* Setting mandatory output values */
  *nreturn_vals = 1;                         // You are dereferencing and chugging in the value 1
  *return_vals = values;                     // You are dereferencing and chugging in the array values 

  values[0].type = GIMP_PDB_STATUS;
  values[0].data.d_status = status;

  /* Getting run_mode - we won't display a dialog if
* we are in NONINTERACTIVE mode */
  run_mode = param[0].data.d_int32;

  /* gimp_procedural_db_query
     gimp_procedural_db_query (const gchar *name, const gchar *blurb, const gchar *help, const gchar *author, const gchar *copyright, const gchar *date, const gchar *proc_type, gint *num_matches, gchar ***procedure_names);

   ".*" means that we have to search for everything.   
The * means match zero or more of anything in wildcards. As we learned, we do this is regular expression with the punctuation mark and the * quantifier. This gives: 

   */




 
  gchar **procnames;
  gint nprocs ;
  gimp_procedural_db_query (".*", ".*",".*",".*",".*",".*",".*",&nprocs, &procnames);
  
  
  
  /* gchar *proceduralname;
  gchar *blurb;
  gchar *help;
  gchar *author;
  gchar *copyright;
  gchar *date;
  GimpPDBProcType proc_type;
  gint num_args;
  gint numvalues;
  GimpParamDef *args;
  GimpParamDef *return_valuess;
  gimp_procedural_db_proc_info ("gimp-image-new", &blurb, &help,&author,&copyright,&date,&proc_type, &num_args, &numvalues, &args, &return_valuess);*/
  

   gint i;
   for (i=0; i<nprocs; i++){
  printf("%04d: %s\n", i, procnames[i]);

  // printf ("Printing out Number of Arguments : %d\n", num_args); 

  /* GimpParam *return_valsss;
  gint nreturn_valsss;
  gint32 layer_ID = -1;
  gint32 drawable_ID;
  gint offx;
  gint offy; 

  return_valsss = gimp_run_procedure ("gimp_selection_float",
				    &nreturn_valsss,
				    GIMP_PDB_DRAWABLE, drawable_ID,
				    GIMP_PDB_INT32, offx,
				    GIMP_PDB_INT32, offy,
				    GIMP_PDB_END);

  gint i;
  for (i = 0; i< nreturn_valsss; i++)
    {
    printf("%04d : %%\n", i, return_valsss[i]);*/




}


}
