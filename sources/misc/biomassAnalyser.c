#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define BUFF 1000 //Buffer for reading the lines in the document
#define STRBUFF 100 //Buffer for reading each value as individual strings
#define M_PI 3.14159265358979323846 //Pi

typedef struct {
    double x;//X-coordinates
    double y;//y-coordinates
    int nr;//Tree-number
    float dim;//Tree dimension
    float biomas;//Tree biomass
    float crown;//Tree crown-area
    float biocrown;//Biomass by Crown
} tree;

FILE *createfile();
double randomizer(int lower, int upper);
void insertionsort(double array[], int size);
void createmap(FILE *data, tree forestdata[], tree trees, double xs[], double ys[], int size);
void getAverage(char filename[], int radius, int replications, int samples, tree forestdata[],
                double xs[], double ys[], int size, double f, double f2, double totA);

/**
 * Program Biomass-Analyser that creates a forestation map based on an input file and runs three different tests.
 * They involve randomizing locations on the map and evaluating how many trees fall into a certain radius from
 * each random-given locations. The three tests all use a different radius but the same randomized locations. Two
 * of the tests use a dynamic radius based on a user-given variable and one test a static radius that is given by the user.
 * Input from the user tells the program hom many randomized locations should be created (samples) and how many times
 * this process should be repeated (replications). The evaluated data is then output to a .csv document.
 */
int main(void) {
    char filename[20];
    int size;//Input for the size-file. Necessary to run the program easier. Because of technical restrictions,
    //the file would have to be read two times otherwise. 
    printf("Please enter the name of your file: ");
    scanf("%s", filename);

    printf("Please enter the number of rows in your file: ");
    scanf("%d", &size);

    FILE *data;
    size = size - 1;
    int radius;//Store input for static radius
    int replications;//Store input for number of replications
    int samples;//Store input for number of samples
    double f; //First F constant
    double f2;//Seccond F constant
    double xs[size]; //Array with all x-coordinates
    double ys[size]; //Array with all y-coordinates
    double totA; //Total Area constant
    tree forestdata[size]; //List containing all the trees
    tree tree;

    data = fopen(filename, "r");

    //Create a map based on the file
    createmap(data, forestdata, tree, xs, ys, size);
    fclose(data);
    //Sort all coordinates so that the map can be created (Figure out the lowest and highest coordinate values)
    insertionsort(xs, size);
    insertionsort(ys, size);
    //Create a randomization-seed
    srand(time(0));

    //Take all necessary input data
    printf("Please enter the test-radius: ");
    scanf("%d", &radius);
    printf("Please enter number of replications: ");
    scanf("%d", &replications);
    printf("Please enter number of plots: ");
    scanf("%d", &samples);
    printf("Enter F1 constant: ");
    scanf("%lf", &f);
    printf("Enter F2 constant: ");
    scanf("%lf", &f2);
    printf("Enter total Area: ");
    scanf("%lf", &totA);

    getAverage(filename,radius,replications,samples,forestdata,xs,ys,size, f, f2, totA);

    return 0;
}

/**
 * Reads the input file and saves all necessary data from it, creating a map
 * @data: Pointer to a file containing the forest information.
 * @forestdata: a 1d array containing trees for building the map. Acts as a table
 * @trees: tree to use for saving data.
 * @xs: 1d array to save all the x-coordinates
 * @ys: 1d array to save all the y-coordinates
 */
void createmap(FILE *data, tree forestdata[], tree trees, double xs[], double ys[], int size) {
    if (data == NULL) {
        printf("Error,  file does not exist in the correct directory\n");
        fclose(data);
        exit(EXIT_FAILURE);
    }
    char treenr[STRBUFF];
    char treedim[STRBUFF];
    char treex[STRBUFF];
    char treey[STRBUFF];
    char treebiomas[STRBUFF];
    char biopercrown[STRBUFF];
    char crown[STRBUFF];
    char line[BUFF];
    fgets(line, BUFF, data);
    for (int i=0; i<size; i++) {
    	fgets(line, BUFF, data);
        //Read everything as strings and then use atof/atoi to transform to float/integer.
        sscanf(line, "%s %*s %s %s %s %s %s %s", treenr, treedim, crown, treex, treey, treebiomas, biopercrown);
        trees.nr = atoi(treenr);
        trees.dim = atof(treedim);
        trees.x = atof(treex);
        xs[i] = atof(treex);
        ys[i] = atof(treey);
        trees.y = atof(treey);
        trees.biomas = atof(treebiomas);
        trees.crown = atof(crown);
        trees.biocrown= atof(biopercrown);

        forestdata[i] = trees;     
    }
}

/**
 * Sorts all the values in a given array based on the insertion sort algorithm.
 * Not very effective but good for this simple purpose since it's easy to implement and use
 * @array: array to sort
 * @size: size of the array
 */
void insertionsort(double array[], int size) {
    double next;
    int temp;
    for (int i = 0; i < size; i++) {
        next = array[i];
        temp = i-1;
        while (temp>=0 && next < array[temp]) {
            array[temp+1] = array[temp];
            temp = temp - 1;
        }
        array[temp+1] = next;
    }
}

/**
 * Create a random number between a given lower and upper limit
 * @lower: lower limit of the random seed
 * @upper: upper limit of the random seed
 * 
 * @return: doulbe num, a random number
 */
double randomizer(int lower, int upper) {
    double num = (rand()%(upper-lower+1)) + lower;
    return num;
}

/**
 * Creates a new file for the output data.
 * 
 * @return: saveData, a file containing the save data. 
 */
FILE *createfile() {
    FILE *saveData;
    char savename[16];
    printf("\nEnter a name for your new savefile. Remember to put .csv in the end.\n");
    printf("No whitespace. Maximum 12 characters: ");
    scanf("%s", savename);
    saveData=fopen(savename, "w");

    if(saveData == NULL) {
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

    return saveData;
}

/**
 * Do the samples and get the average for the total biomass of the samples in each run and
 * output the data into a .csv file. 
 * 
 * @filename: the name of the file that was read
 * @radius: radius that is used for the samples
 * @replications: number of replications
 * @sampless: number of sampless
 * @forestdata: array containing information about all the trees
 * @xs: array containing all the x-coordinates
 * @ys: array containing all the y-coordinates
 * @size: size of the file that was read 
 */
void getAverage(char filename[], int radius, int replications, int samples, tree forestdata[],
                double xs[], double ys[], int size, double f, double f2, double totA) {
    double xrand; //randomized x-coordinate
    double yrand; //randomized y-coordinate
    double xlow; //lowest limit for randomization in x-axis
    double xhigh; //highest limit for randomization in x-axis
    double ylow; // lowest limit for randomization in y-axis
    double yhigh; //highest limit for randomization i y-axis

    double rad; //variable for the dynamic radius created based on F1 
    double rad2; //variable for the dynamic radius created based on F2
    double nrOfTreesF1; //Number of trees which fall into the dynamic radius
    double nrOfTreesF2;//Number of trees which fall into the seccond dynamic radius

    double realScope;
    double totalbiomass; //Total biomass
    double averagebiomass; //Average biomass
    double baselArea;//Self-explainatory
    double averageNrOfTreesF1; //average for nrOfTreesF1
    double vTimesB;//output

    double biomass = 0;//Variable for total biomass
    double biomaspercrown = 0;// Biomass divided by Crownarea
    double averagebiomaspercrown = 0;

    //Create new file for data-output. 
    FILE *saves = createfile();

    //Print the file-header
    fprintf(saves, 
            "Filename:%s. Radius: %d. F1: %lf. F2: %lf. Nr of samples: %d. Nr of replications: %d;Average Biomass; Number of Trees F1;"
             "Number of Trees F2; V*B; realscope\n",
            filename, radius,f, f2, samples, replications);
    
    //Start taking the samples
    for (int i=0; i<replications; i++) {
        //Print the run number
        fprintf(saves,"Run nr%d;", i+1);

        //Repeat following actions for each sample-point
        for (int i1=0; i1<samples; i1++) {

            //Choose a random location in the map
            xrand = randomizer(xs[0], xs[size-1]);
            yrand = randomizer(ys[0], ys[size-1]);

            //Mark the area in which the evaluations will be made
            xlow = xrand-radius;
            xhigh = xrand+radius;
            ylow = yrand-radius;
            yhigh = yrand+radius;

            //Loop through all the trees and check which ones fall into the test area
            for (int i2=0; i2<size; i2++) {

                //Static radius, if the tree matches both the x-axis margin and y-axis margin AND the radius limit,
                //add it's biomass to the total biomass
                if (forestdata[i2].x < xhigh && forestdata[i2].x > xlow) {
                    if (forestdata[i2].y < yhigh && forestdata[i2].y > ylow) {
                        //Pythagora
                        if(sqrt(pow((xrand-forestdata[i2].x), 2)+pow((yrand-forestdata[i2].y), 2)) <= radius) {
                        biomass = biomass + forestdata[i2].biomas;
                        }
                    }
                }

                //Dynamic radius, first constant
                rad = forestdata[i2].dim/(2*sqrt(f));
                //Pythagora based on the dynamic radius
                if(sqrt(pow((xrand-forestdata[i2].x), 2)+pow((yrand-forestdata[i2].y), 2)) <= rad) {
                    nrOfTreesF1 = nrOfTreesF1+1;
                }
                //Dynamic radius, seccond constant
                rad2 = forestdata[i2].dim/(2*sqrt(f2));
                //Pythagora based on the dynamic radius
                if(sqrt(pow((xrand-forestdata[i2].x), 2)+pow((yrand-forestdata[i2].y), 2)) <= rad2) {
                    nrOfTreesF2 = nrOfTreesF2+1;
                    biomaspercrown = biomaspercrown + forestdata[i2].biocrown;
                }
            }
            //Fix plot
            biomass = biomass/((pow(radius,2)*M_PI)/10000);
            biomass = biomass*totA;
            totalbiomass = totalbiomass + biomass;
            biomass = 0;
        }


        averagebiomass = totalbiomass/samples;
        averageNrOfTreesF1 = nrOfTreesF1/samples;
        averagebiomaspercrown = biomaspercrown/nrOfTreesF2;
        baselArea = f*averageNrOfTreesF1*totA;
        vTimesB = baselArea*averagebiomaspercrown;
        realScope = biomaspercrown * f2 * totA;
        realScope = realScope/samples;


        fprintf(saves, "%.1lf;%.0lf;%.0lf;%.1lf;%.1lf\n", averagebiomass, nrOfTreesF1, nrOfTreesF2, vTimesB, realScope);
        
        //Reset necessary variables
        totalbiomass = 0;
        biomaspercrown = 0;
        nrOfTreesF1 = 0;
        nrOfTreesF2 = 0;
    }

    fclose(saves);
}
