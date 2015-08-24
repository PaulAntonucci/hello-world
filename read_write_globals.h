//#include <userint.h>

#ifndef READ_WRITE_GLOBALS_H
#define READ_WRITE_GLOBALS_H



#include <QDataStream>

/* defines */
#define PANELS          66						 /* number of panels */

#define FLOWCHANNELS     4                       /* number of flow channels */
#define ABLATIONLASERS   2                       /* number of ablation lasers */
#define NUM_VARIABLES   12                       /* number of fit variables */
#define RES_VARIABLES    8						 /* reserved number of variables */
#define NUM_FLAGS        2					     /* number of fit flags */
#define RES_FLAGS    	 3                       /* reserved number of flags */
#define MAX_PROFILES    15					     /* number of fit profiles */
#define RES_PROFILES    25                       /* reserved number of profiles */
#define NUM_RSC         12                       /* number of rsc */
#define MAX_LABLE_LEN   26                       /* length of lable string */
#define MAX_RSC_LEN     26                       /* length of rsc string */
#define MAX_HPGL_LEN    21                       /* length of HPGL string */
#define MAX_LINE_LEN    81                       /* length of line string */
#define HALF_LINE_LEN   41                       /* length of half line string */
#define MAX_ORAVAL_LEN  26                       /* length of ORACLE value string */
#define MAX_ORALN_LEN  500						 /* length of ORACLE line string */ 
#define SIZE_OF_STRING  64						 /* size of string variable */
#define RECORDS          5						 /* multiple records */
//#define RECORDS       10						 /* multiple records */
#define SIDES			 2						 /* complex time domain */
#define COUNTS      262144						 /* record length */
#define TRANS	   1048576                       /* transform length */
//#define COUNTS    131072						 /* record length */
//#define TRANS	    524288                       /* transform length */
//#define COUNTS     16384						 /* record length */
//#define TRANS	     65536                       /* transform length */
#define SIGNALS          2                       /* TD signal types */  
#define TRACES           4                       /* TD traces */
#define SPECTRA          4                       /* FD spectra */
#define REPRESENTATIONS  2						 /* FD representations */
#define SPARAMETER		 4                       /* S-Parameter traces */
#define SINGLE		     1                       /* single trace */
#define REAL             1                       /* 1D data*/
#define IMAGINARY        1                       /* 1D data*/
#define COMPLEX  		 2                       /* 2D data*/
#define XY		         2                       /* 2D data*/
#define LINES         1601                       /* list length */
#define POINTS        1601						 /* trace length */
#define STEPS        16001						 /* survey length */
#define WAFER_MEAS      11                       /* DK and tan(delta), z[3] , nu[3], Q[3]*/
#define WAFER_ROWS      11                       /* Rows on wafer */
#define WAFER_COLS      11                       /* Columns on wafer */
#define MAP_POINTS       8                       /* Points of response map */  


//PRAA
#define MAX_PATHNAME_LEN    255
#define MAX_FILENAME_LEN    255
#define MAX_DIRNAME_LEN     255
#define MAX_DRIVENAME_LEN   255

#define FILE    QFile



/* Type definitions */
typedef char      Line[MAX_LINE_LEN];
typedef char      Lable[MAX_LABLE_LEN];
typedef char      Rsc[MAX_RSC_LEN];
typedef char      JensString[SIZE_OF_STRING];



typedef struct panelpar
        {
        JensString version;
        JensString revision;
        JensString system;
        JensString author;
        JensString institution;
        JensString reservedstrings[15];
		int    counts;
		int    sides;
		int    target;
		int    actual;
		int    points;
		int    reservedints[15];
        double span;
        double interval;
        double nyquistfreq;
        double resolution;
        double excfreq;
        double convband;
        double sweep;
        double bandwidth;
        double backgroundmean;
        double backgroundwidth;
        double backgroundampl;
        double backgroundcoupl;
        double foregroundmean;
        double foregroundwidth;
        double foregroundampl;
        double foregroundcoupl;
        double loadmean;
        double loadwidth;
        double loadampl;
        double loadcoupl;
        double sampledist;
        double samplethick;
        double sampleeps;
        double sampletan;
        double reserveddoubles[16];

        friend QDataStream & operator >> ( QDataStream & s, panelpar & x )
        {
            s.readRawData(x.version, 64);
            s.readRawData(x.revision, 64);
            s.readRawData(x.system, 64);
            s.readRawData(x.author, 64);
            s.readRawData(x.institution, 64);
            s.readRawData(x.reservedstrings[0], 960); // 15 of the 64 char Jensstrings
            s>> x.counts; s>>x.sides; s>>x.target; s>>x.actual; s>> x.points;
            int index;
            for(index=0;index<15;index++)s>>x.reservedints[index];

            s >> x.span;
            s >> x.interval;
            s >> x.nyquistfreq;
            s >> x.resolution;
            s >> x.excfreq;
            s >> x.convband;
            s >> x.sweep;
            s >> x.bandwidth;
            s >> x.backgroundmean;
            s >> x.backgroundwidth;
            s >> x.backgroundampl;
            s >> x.backgroundcoupl;
            s >> x.foregroundmean;
            s >> x.foregroundwidth;
            s >> x.foregroundampl;
            s >> x.foregroundcoupl;
            s >> x.loadmean;
            s >> x.loadwidth;
            s >> x.loadampl;
            s >> x.loadcoupl;
            s >> x.sampledist;
            s >> x.samplethick;
            s >> x.sampleeps;
            s >> x.sampletan;
            for(index = 0;index<16;index++) s >> x.reserveddoubles[index];
            return( s );
        }
        }
        Panelpar;
typedef struct tunefrequencypar
        {
        JensString reservedstrings[20];
    	int    method;
		int    reservedints[19];
        double sweep;
        double move;
        double power;
        double handover;
        double resolution;
        double frequency;
        double xcoarsevelset;
        double ycoarsevelset;
        double zcoarsevelset;
        double xcoarseposbound;
        double sensorbound;
        double xcoarsevelbound;
        double preamp;
        double reserveddoubles[27];

        friend QDataStream & operator >> ( QDataStream & s, tunefrequencypar & x )
        {
            s.readRawData(x.reservedstrings[0], 1280); // 20 of the 64 char Jensstrings

            s >> x.method;
            int index;
            for(index = 0;index<19;index++) s >> x.reservedints[index];
            s >> x.sweep;
            s >> x.move;
            s >> x.power;
            s >> x.handover;
            s >> x.resolution;
            s >> x.frequency;
            s >> x.xcoarsevelset;
            s >> x.ycoarsevelset;
            s >> x.zcoarsevelset;
            s >> x.xcoarseposbound;
            s >> x.sensorbound;
            s >> x.xcoarsevelset;
            s >> x.preamp;
            for(index = 0;index<27;index++) s >> x.reserveddoubles[index];
            return( s );
        }

        }
        Tunefrequencypar;
typedef struct adjustparameterpar
        {
        JensString reservedstrings[20];
		int    method;
		int    reservedints[19];
        double detectiond;
        double protectiond;
        double protectionw;
        double recoveryd;
        double recoveryw;
        double transferd;
        double transferw;
        double excitationd;
        double excitationw;
        double expansion;
        double unloadd;
        double unloadw;
        double sourced;
        double sourcew;
        double loadd;
        double loadw;
        double unload2d;
        double unload2w;
        double source2d;
        double source2w;
        double iond;
        double ionw;
        double flow1;
        double flow2;
        double flow3;
        double flow4;
        double pressure;
        double temperature;
        double dischrgfield;
        double dischrgdensity;
        double ablationleft;
        double ablationright;
        double excpow;
        double excfreq;
        double drpow;
        double drfreq;
        double selectd;
        double selectw;
        double load2d;
        double load2w;
        friend QDataStream & operator >> ( QDataStream & s, adjustparameterpar & x )
        {
            s.readRawData(x.reservedstrings[0], 1280); // 20 of the 64 char Jensstrings

            s >> x.method;
            int index;
            for(index = 0;index<19;index++) s >> x.reservedints[index];
            s >> x.detectiond;
            s >> x.protectiond;  s >> x.protectionw;
            s >> x.recoveryd;    s >> x.recoveryw;
            s >> x.transferd;    s >> x.transferw;
            s >> x.excitationd;  s >> x.excitationw;
            s >> x.expansion;
            s >> x.unloadd;     s>>x.unloadw;    s >> x.sourced;    s>>x.sourcew;
            s >> x.loadd;     s>>x.loadw;             s >> x.unload2d;     s>>x.unload2w;
            s >> x.source2d;    s>>x.source2w;
            s >> x.iond;        s>>x.ionw;
            s >> x.flow1;       s>>x.flow2;   s>>x.flow3;   s>>x.flow4;
            s >> x.pressure;    s>>x.temperature;
            s >> x.dischrgfield;            s >> x.dischrgdensity;
            s >> x.ablationleft;            s >> x.ablationright;
            s >> x.excpow;            s >> x.excfreq;
            s >> x.drpow;            s >> x.drfreq;
            s >> x.selectd;            s >> x.selectw;
            s >> x.load2d;            s >> x.load2w;
            return (s);
        }

        }
        Adjustparameterpar;
typedef struct setfieldspar
        {
        JensString reservedstrings[20];
		int    reservedints[20];
        double excpow;
        double excfreq;
        double drpow;
        double drfreq;
        double efield;
        double hfield;
        double reserveddoubles[34];
        friend QDataStream & operator >> ( QDataStream & s, setfieldspar & x )
        {
            s.readRawData(x.reservedstrings[0], 1280); // 20 of the 64 char Jensstrings
            int index;
            for(index = 0;index<20;index++) s >> x.reservedints[index];
            s >> x.excpow;
            s >> x.excfreq;
            s >> x.drpow;
            s >> x.drfreq;
            s >> x.efield;
            s >> x.hfield;
            for(index = 0;index<34;index++) s >> x.reserveddoubles[index];
            return( s );
        }

        }
        Setfieldspar;	 
typedef struct setsequencepar
        {
        JensString reservedstrings[20];
    	int    detection;
    	int    protection;
    	int    recovery;
    	int    transfer;
    	int    excitation;
    	int    unload;
    	int    source;
    	int    load;
    	int    unload2;
    	int    source2;
    	int    ion;
    	int    select;
    	int    load2;
		int    reservedints[7];
        double detectiond;
        double protectiond;
        double protectionw;
        double recoveryd;
        double recoveryw;
        double transferd;
        double transferw;
        double excitationd;
        double excitationw;
        double expansion;
        double unloadd;
        double unloadw;
        double sourced;
        double sourcew;
        double loadd;
        double loadw;
        double unload2d;
        double unload2w;
        double source2d;
        double source2w;
        double iond;
        double ionw;
        double selectd;
        double selectw;
        double load2d;
        double load2w;
        double reserveddoubles[14];
        friend QDataStream & operator >> ( QDataStream & s, setsequencepar & x )
        {
            s.readRawData(x.reservedstrings[0], 1280); // 20 of the 64 char Jensstrings
            int index;  // throw away data we won't be looking at
            for(index = 0;index<20;index++) s >> x.reservedints[0];
            for(index = 0;index<40;index++) s >> x.reserveddoubles[0];
            return( s );
        }

        }
        Setsequencepar;
typedef struct setwaveformpar
        {
        JensString reservedstrings[20];
		int    counts;
    	int    sides;
    	int    records;
    	int    adcres;
		int    reservedints[16];
        double span;
        double interval;
        double nyquistfreq;
        double resolution;
        double band;
        double gain;
        double sideband;
        double shift;
        double width;
        double begin;
        double end;
        double beginif;
        double endif;
        double adcrange;
        double time;
        double phase;
        double extdist;
        double accdist;
        double driftdist;
        double extvolt;
        double accvolt;
        double bandwidth;
        double reserveddoubles[18];
        friend QDataStream & operator >> ( QDataStream & s, setwaveformpar & x )
        {
            s.readRawData(x.reservedstrings[0], 1280); // 20 of the 64 char Jensstrings
            s >> x.counts;
            s >> x.sides;
            s >> x.records;
            s >> x.adcres;
            int index;
            for(index = 0;index<16;index++) s >> x.reservedints[0];
            for(index = 0;index<40;index++) s >> x.reserveddoubles[0];
            return( s );
        }

        }
        Setwaveformpar;
typedef struct setenvironmentpar
        {
        JensString reservedstrings[20];
    	int    idleenable;
    	int    measbuffer;
    	int    adjbuffer;
    	int    number;
    	int    incr;
        int    type;
        int    symmetry;
        int    sample;
        int    averageallow;
        int    measdiscard;
		int    reservedints[10];
        double acquire;
        double idlerate;
        double DUMMY_1;
        double DUMMY_2;
        double fronttemp;
        double reartemp;
        double diameter;
        double distance;
        double DUMMY_3;
        double depth;
        double conduct;
        double width;
        double height;
        double rearcurv;
        double frontcurv;
        double transmitcoupl;
        double receivecoupl;
        double inner;
        double outer;
        double decaygap;
        double decayloss;
        double loss;
        double reserveddoubles[18];
        friend QDataStream & operator >> ( QDataStream & s, setenvironmentpar & x )
        {
            s.readRawData(x.reservedstrings[0], 1280); // 20 of the 64 char Jensstrings
            int index;
            for(index = 0;index<20;index++) s >> x.reservedints[0];
            for(index = 0;index<40;index++) s >> x.reserveddoubles[0];
            return( s );
        }
        }
        Setenvironmentpar;
typedef struct setsamplepar
        {
        JensString name;
        JensString formula;
        JensString rotation;
        JensString internal;
        JensString nuclear;
        JensString sample;
        JensString nozzle;
        JensString unused[2];
        JensString date;
        JensString time;
        JensString version;
        JensString revision;
        JensString system;
        JensString reservedstrings[6];
		int    reservedints[20];
        double gas1;
        double gas2;
        double gas3;
        double gas4;
        double corr1;
        double corr2;
        double corr3;
        double corr4;
        double pressure;
        double temperature;
        double weight;
        double flow1;
        double flow2;
        double flow3;
        double flow4;
        double reserveddoubles[25];
        friend QDataStream & operator >> ( QDataStream & s, setsamplepar & x )
        {
            s.readRawData(x.name, 64);
            s.readRawData(x.formula, 64);
            s.readRawData(x.rotation, 64);
            s.readRawData(x.internal, 64);
            s.readRawData(x.nuclear, 64);
            s.readRawData(x.sample, 64);
            s.readRawData(x.nozzle, 64);
            s.readRawData(x.unused[0], 64);
            s.readRawData(x.unused[1], 64);
            s.readRawData(x.date, 64);
            s.readRawData(x.time, 64);
            s.readRawData(x.version, 64);
            s.readRawData(x.revision, 64);
            s.readRawData(x.system, 64);
            s.readRawData(x.reservedstrings[0], 384); // 6  of the 64 char Jensstrings
            int index;
            for(index = 0;index<20;index++) s >> x.reservedints[0];
            s >> x.gas1 >>x.gas2 >> x.gas3 >> x.gas4;
            s >> x.corr1 >> x.corr2 >> x.corr3 >> x.corr4;
            s >> x.pressure >> x.temperature >>x.weight;
            s >> x.flow1 >> x.flow2 >> x.flow3 >> x.flow4;
            for(index = 0;index<25;index++) s >> x.reserveddoubles[0];
            return( s );
        }
        }
        Setsamplepar;
typedef struct setsuccessionpar
        {
        JensString reservedstrings[20];
    	int    objective;
    	int    elements;
    	int    save;
    	int    print;
    	int    finetune;
    	int    overwrite;
        int    exportPRAA;
		int    reservedints[13];
        double increment;
        double treshold;
        double start;
        double inc;
        double stop;
        double reserveddoubles[35];

        friend QDataStream & operator >> ( QDataStream & s, setsuccessionpar & x )
        {
            s.readRawData(x.reservedstrings[0], 1280); // 6  of the 64 char Jensstrings
            int index;
            for(index = 0;index<20;index++) s >> x.reservedints[0];
            for(index = 0;index<40;index++) s >> x.reserveddoubles[0];
            return( s );
        }

        }
        Setsuccessionpar;
typedef struct setsurveypar
        {
        JensString reservedstrings[20];
    	int    objective;
    	int    elements;
    	int    save;
    	int    print;
    	int    finetune;
    	int    overwrite;
    	int    tune;
        int    exportPRAA;
		int    reservedints[12];
        double increment;
        double treshold;
        double start;
        double inc;
        double stop;
        double reserveddoubles[35];
        friend QDataStream & operator >> ( QDataStream & s, setsurveypar & x )
        {
            s.readRawData(x.reservedstrings[0], 1280); // 6  of the 64 char Jensstrings
            int index;
            for(index = 0;index<20;index++) s >> x.reservedints[0];
            for(index = 0;index<40;index++) s >> x.reserveddoubles[0];
            return( s );
        }
        }
        Setsurveypar;
typedef struct set2Dpar
        {
        JensString reservedstrings[20];
    	int    objective;
    	int    auxobjective;
    	int    elements;
    	int    auxelements;
    	int    overwrite;
        int    exportPRAA;
		int    reservedints[14];
        double increment;
        double auxincrement;
        double start;
        double auxstart;
        double inc;
        double auxinc;
        double stop;
        double auxstop;
        double nyquist;
        double resolution;
        double reserveddoubles[30];
        friend QDataStream & operator >> ( QDataStream & s, set2Dpar & x )
        {
            s.readRawData(x.reservedstrings[0], 1280); // 6  of the 64 char Jensstrings
            int index;
            for(index = 0;index<20;index++) s >> x.reservedints[0];
            for(index = 0;index<40;index++) s >> x.reserveddoubles[0];
            return( s );
        }
        }
        Set2Dpar;
typedef struct setlibrarypar
        {
        JensString reservedstrings[20];
    	int    rows;
    	int    cols;
		int    reservedints[18];
        double idia;
        double bottomrow;
        double incrrow;
        double modrow;
        double leftcol;
        double incrcol;
        double modcol;
        double height;
        double width;
        double eps;
        double tan;
        double thickness;
        double gap;
        double odia;
        double reserveddoubles[26];
        friend QDataStream & operator >> ( QDataStream & s, setlibrarypar & x )
        {
            s.readRawData(x.reservedstrings[0], 1280); // 6  of the 64 char Jensstrings
            int index;
            for(index = 0;index<20;index++) s >> x.reservedints[0];
            for(index = 0;index<40;index++) s >> x.reserveddoubles[0];
            return( s );
        }
        }
        Setlibrarypar;
typedef struct responseparameterpar
        {
        JensString reservedstrings[20];
    	int    validload;
    	int    validunload;
    	int    validcalculate;
    	int    validprobe;
		int    reservedints[16];
        double center[8];
        double span[8];
        double reserved[8];
        double coupling[8];
        double unloadcenter;
        double unloadspan;
        double unloadamplitude;
        double unloadcoupling;
        double gridincr;
        double unloaddistance;
        double reserveddoubles[2];
        friend QDataStream & operator >> ( QDataStream & s, responseparameterpar & x )
        {
            s.readRawData(x.reservedstrings[0], 1280); // 6  of the 64 char Jensstrings
            int index;
            for(index = 0;index<20;index++) s >> x.reservedints[0];
            for(index = 0;index<40;index++) s >> x.reserveddoubles[0];
            return( s );
        }
        }
        Responseparameterpar;
typedef struct setiterationpar
        {
        JensString reservedstrings[20];
    	int    iterations;
    	int    total;
    	int    ties;
    	int    line;
    	int    tie;
    	int    elements;
		int    reservedints[14];
        double lorentzbroad;
        double gaussbroad;
        double lorentzcobra;
        double gausscobra;
        double doppler;
        double snr;
        double width;
        double height;
        double separation;
        double rofit;
        double decaygap;
        double decayloss;
        double loss;
        double reserveddoubles[27];
        friend QDataStream & operator >> ( QDataStream & s, setiterationpar & x )
        {
            s.readRawData(x.reservedstrings[0], 1280); // 6  of the 64 char Jensstrings
            int index;
            for(index = 0;index<20;index++) s >> x.reservedints[0];
            for(index = 0;index<40;index++) s >> x.reserveddoubles[0];
            return( s );
        }
        }
        Setiterationpar;
typedef struct setprofilespar
        {
        JensString reservedstrings[20];
        int    element;
        int    ties;
        int    line;
        int    iteration;
		int    cycle;
		int    reservedints[15];
        double alamda;
        double chisq;
        double reserveddoubles[38];
        friend QDataStream & operator >> ( QDataStream & s, setprofilespar & x )
        {
            s.readRawData(x.reservedstrings[0], 1280); // 6  of the 64 char Jensstrings
            int index;
            for(index = 0;index<20;index++) s >> x.reservedints[0];
            for(index = 0;index<40;index++) s >> x.reserveddoubles[0];
            return( s );
        }
        }
        Setprofilespar;
typedef struct reservedpar
        {
        JensString reservedstrings[20];
		int    reservedints[20];
        double reserveddoubles[40];
        friend QDataStream & operator >> ( QDataStream & s, reservedpar & x )
        {
            s.readRawData(x.reservedstrings[0], 1280); // 6  of the 64 char Jensstrings
            int index;
            for(index = 0;index<20;index++) s >> x.reservedints[0];
            for(index = 0;index<40;index++) s >> x.reserveddoubles[0];
            return( s );
        }
        }
        Reservedpar;


#endif
