#define var GLfloat
//####################################################################################################################

#ifdef WIN32
        #define   glGenerateMipmap       glGenerateMipmapEXT
        #define   glGenFramebuffers      glGenFramebuffersEXT
        #define   glBindFramebuffer      glBindFramebufferEXT
        #define   glFramebufferTexture2D glFramebufferTexture2DEXT
         
        #define   STRICT
        #define   WIN32_LEAN_AND_MEAN
        #include <windows.h>
        #include <iostream.h>
        #include <fstream.h>
        //using namespace std; //___used for string object

        //-----------------------------------------------------------------------------

        #include <GL/gl.h>
        #include <GL/glu.h>
        #include "headerFiles/glext.h"
        #include "headerFiles/glext_Init_A.cpp"

        void InitGL(void);
        void RenderGL(void);
        
        void ProcessKeyboard(void);
                
        var  viewWidth;
        var  viewHeight;
        
        //----------------------------------------------------------------------
        GLfloat  PassMouseMovement[2];

        //-------------------------------
        var keys[256], keypressed[256];
        #include "cpp/WGL_ARB_multisample.h"
        //-------------------------------

        #include "headerFiles/VSync.h"
        
        #include <windows.h>

        void      ConfigureAndLoadTexture(GLubyte *textureData, GLint texWidth, GLint texHeight );
        #include "headerFiles/glaux.h"
        #include "headerFiles/FreeImage.h"
        #include "cpp/freeImage.cpp"
        //------------------------------------------
 
#endif

//####################################################################################################################

        GLfloat  PassTouchMovement[3];

//####################################################################################################################

#include <math.h>
  
//####################################################################################################################

#include "MATRIX_MATH.cpp"

//####################################################################################################################

//--------------------------------------------------------------------------------------------------------------
#define BUFFER_OFFSET(i) ((char *)0 + (i))
//----------------------------------------------------------------------------------------

        extern GLuint msaaFramebuffer;

        void RenderGL(void);
        void InitGL  (void);
        void shutDownGL(void);
      
        #ifdef __APPLE__
               var viewWidth;
               var viewHeight;
               GLuint  viewFramebuffer;
        #endif
          
        //-------------------------------------------------------------------------------


GLuint m_uiShadowMapTexture;
GLuint m_uiFrameBufferObject;



//#########################################################################################################


void ConfigureAndLoadTexture(GLubyte *textureData, GLint texWidth, GLint texHeight )
{

        #ifdef __APPLE__
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
        #endif
        
        #ifdef WIN32
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE );
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, textureData);
        #endif
}

//===============================================================================================================================


var     modelView[16];
var     projection[16];
var     mvpMatrix[16];
var     mvpMatrixInverse[16];
var     lightMatrix[16];
var     moveSetMatrix[16];
var     ProjectionShadow[16];
var     modelViewShadow[16];
var     viewMatrix[16];

var     LightModelViewMatrix[16];


float   modelWorld[16];
float   LightView[16];
float   LightProjection[16];
float   modelViewInverse[16];

float   tempMatrix[16];

var     textureMatrix[16] = {   0.5f, 0.0f, 0.0f, 0.0f,
                                0.0f, 0.5f, 0.0f, 0.0f,
                                0.0f, 0.0f, 0.5f, 0.0f,
                                0.5f, 0.5f, 0.5f, 1.0f   };

var     inverseMatrix[16];


//============================================================================================================================

var     moveShadowPivot_Z = 0.0;



//---------------------------------------------------------------------------------------
var           fieldOfView                                      =     30.0;
var           adjustNearFar[]                                  =  {  0.1, 250.0 };
//---------------------------------------------------------------------------------------
var           moveSet[]                                        =  {  0.0, 0, 0.0, 1.0};
//---------------------------------------------------------------------------------------
var           eyepositionCamera[]                              =  {  0, 0.0, 0.0, 0.0};
//---------------------------------------------------------------------------------------
var           eyeposition[]                                    =  {0, 0.0, 30.2, 0.0};
var           lookAt[]                                         =  {0,  0.0, 0, 0.0};
var           rotateModelWithLeftMouse[]                       =  {0, 0};
//---------------------------------------------------------------------------------------
var           upVector[]             	                       =  {  0.0, 1.0, 0.0};
//---------------------------------------------------------------------------------------
GLuint        boxCount = 0;
var           collisionBoxArray[1000][7];    

bool          modelCanMoveLeft = true;                      
bool          modelCanMoveRight = true;  
bool          modelCanMoveDown = true;                      
bool          modelCanMoveUp = true; 
bool          modelCanMoveNear = true;                      
bool          modelCanMoveFar = true; 

bool          boxCollisionHasOccured = false;

bool          exitCollisionTest = false;

bool          animateSet = false;

bool          R_keyIsReset = true;

bool          modelIsMovingLeft  = false;
bool          modelIsMovingRight = false;
bool          modelIsMovingDown  = false;
bool          modelIsMovingUp    = false;
//===========================================================================================================================================
void CollisionTest( GLfloat leftEdge,            GLfloat rightEdge, 
                        GLfloat bottomEdge,          GLfloat topEdge, 
                        GLfloat farEdge,             GLfloat nearEdge, 
                        GLfloat model_ID,   
                        GLfloat velocity_X,          GLfloat velocity_Y,        GLfloat velocity_Z,
                        GLfloat bounceFactor_X,      GLfloat bounceFactor_Y,    GLfloat bounceFactor_Z,
                        GLfloat updateCollisionInfo
                        );

//===========================================================================================================================================
                               
                            
                            
                               //====================================================================================
                               #include "_SHADERS/plastic/rubber/rubber_SHADER_GLOBALS.cpp"
                               //====================================================================================
                               //#####################################___MODELS___#######################################################
                               //====================================================================================
                               #include "_MODEL_FOLDERS_/flowerShield/flowerShield_Globals.cpp"
                               //====================================================================================
                               #include "_MODEL_FOLDERS_/unit_cube/unit_cube_Globals.cpp"                                                                
                               //====================================================================================   
                               
                               
                               //====================================================================================                                                                
                               GLfloat model_01_collisionInfo[14];
                               GLfloat     model_01_POSITION[]            =  {  0.0, 0.0,  0.0, 1.0};
                               GLfloat     model_01_VELOCITY[]            =  {  0.05, 0.05,  0.05, 1.0}; 
                               //=====================================================================
                               GLfloat model_02_collisionInfo[14];
                               GLfloat     model_02_POSITION[]            =  { -3.0, 0.0,  0.0, 1.0};
                               GLfloat     model_02_VELOCITY[]            =  {  0.05, 0.05,  0.05, 1.0};
                               //=====================================================================
                               GLfloat model_03_collisionInfo[14];
                               GLfloat     model_03_POSITION[]            =  {  5.0, 0.0,  0.0, 1.0}; 
                               GLfloat     model_03_VELOCITY[]            =  {  0.05, 0.05,  0.05, 1.0}; 
                               //=====================================================================
                               GLfloat model_04_collisionInfo[14];
                               GLfloat     model_04_POSITION[]            =  {  4.0, 1.0,  0.0, 1.0}; 
                               GLfloat     model_04_VELOCITY[]            =  {  0.05, 0.05,  0.05, 1.0};
                               //=====================================================================


//============================================================================================================================

void setupTransforms_MainColor(void)
{
        LoadIdentity(modelView);
        LookAt(modelView,    eyeposition[0],
                             eyeposition[1],
                             eyeposition[2],
                             lookAt[0],
                             lookAt[1],
                             lookAt[2],
                             upVector[0],
                             upVector[1],
                             upVector[2]);
        
        //--------------------------------------------------------------------------------------
        LoadIdentity(viewMatrix);
        AssignMatrix(viewMatrix, modelView);
        InvertMatrix(viewMatrix, viewMatrix);
        //--------------------------------------------------------------------------------------
        Translate(modelView, moveSet[0] , moveSet[1] , moveSet[2] );
        Rotate(modelView, 1.0, 0.0, 0.0, rotateModelWithLeftMouse[0]);
        Rotate(modelView, 0.0, 1.0, 0.0, rotateModelWithLeftMouse[1]);
}

//####################################################################################################################################################
//====================================================================================================================================================
//====================================================================================================================================================
//####################################################################################################################################################


var shaderNumber = 0;

void SelectShader(var shaderNumber)
{
        
        //--------------------------------------------------------------------------------------
        if(shaderNumber == 26)
        {
                #include "_SHADERS/plastic/rubber/rubber_SHADER_RENDER.cpp"
        }
        //--------------------------------------------------------------------------------------
    
   
}

//####################################################################################################################################################
//====================================================================================================================================================
//====================================================================================================================================================
//####################################################################################################################################################


void InitGL( void )
{//__BEGIN_INIT__@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

        //==========================================================================
        #ifdef WIN32
            #include "cpp/setPixelFormat.cpp"
            #include "headerFiles/glext_Init_B.cpp"
            //-------------------------------------
            SetVSyncState(true);
            //-------------------------------------
            PassMouseMovement[0]        = rotateModelWithLeftMouse[0];
            PassMouseMovement[1]        = rotateModelWithLeftMouse[1];
        #endif
                   

 
        //=================================================================================================================
        #include "_SHADERS/plastic/rubber/rubber_SHADER_INIT.cpp"
        //====================================================================================
        #include "_MODEL_FOLDERS_/flowerShield/flowerShield_Init.cpp"
        //====================================================================================
        #include "_MODEL_FOLDERS_/unit_cube/unit_cube_Init.cpp"                                                                   
        //====================================================================================                                                                

        //====================================================================================   
        model_02_collisionInfo[0] = -4.0;
        model_02_collisionInfo[1] = -2.0;
        model_02_collisionInfo[2] = -1;
        model_02_collisionInfo[3] = 1;
        model_02_collisionInfo[4] = -1;
        model_02_collisionInfo[5] = 1;
        model_02_collisionInfo[6] = boxCount;        
        //------------------------------------=  
        collisionBoxArray[boxCount][0] = -4.0;
        collisionBoxArray[boxCount][1] = -2.0;
        collisionBoxArray[boxCount][2] = -1;
        collisionBoxArray[boxCount][3] = 1;
        collisionBoxArray[boxCount][4] = -1;
        collisionBoxArray[boxCount][5] = 1;
        collisionBoxArray[boxCount][6] = boxCount;
boxCount++;
        //====================================================================================   
        model_03_collisionInfo[0] = 4.0;
        model_03_collisionInfo[1] = 6.0;
        model_03_collisionInfo[2] = -1;
        model_03_collisionInfo[3] = 1;
        model_03_collisionInfo[4] = -1;
        model_03_collisionInfo[5] = 1;
        model_03_collisionInfo[6] = boxCount;        
        //------------------------------------      
        collisionBoxArray[boxCount][0] = 4.0;
        collisionBoxArray[boxCount][1] = 6.0;
        collisionBoxArray[boxCount][2] = -1;
        collisionBoxArray[boxCount][3] = 1;
        collisionBoxArray[boxCount][4] = -1;
        collisionBoxArray[boxCount][5] = 1;
        collisionBoxArray[boxCount][6] = boxCount;
boxCount++;
        //====================================================================================   
        model_04_collisionInfo[0] = 3.0;
        model_04_collisionInfo[1] = 5.0;
        model_04_collisionInfo[2] = 0;
        model_04_collisionInfo[3] = 2;
        model_04_collisionInfo[4] = -1;
        model_04_collisionInfo[5] = 1;
        model_04_collisionInfo[6] = boxCount;        
        //------------------------------------          
        collisionBoxArray[boxCount][0] = 3.0;
        collisionBoxArray[boxCount][1] = 5.0;
        collisionBoxArray[boxCount][2] = 0;
        collisionBoxArray[boxCount][3] = 2;
        collisionBoxArray[boxCount][4] = -1;
        collisionBoxArray[boxCount][5] = 1;
        collisionBoxArray[boxCount][6] = boxCount;
boxCount++;                
        
                        
//====================================================================================================================================


    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LEQUAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glAlphaFunc(GL_GREATER, 0.1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
        
//====================================================================================================================================

    



}//__END_INIT__@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//####################################################################################################################################################
//====================================================================================================================================================
//====================================================================================================================================================
//####################################################################################################################################################



void RenderGL(void)
{
        
        //==========================_UPDATE_COLLISION_ARRAY_USING_MODEL_POSITION__====================================================================
        //=================================================================================
        collisionBoxArray[(GLuint)model_01_collisionInfo[6]][0] = model_01_collisionInfo[0];
        collisionBoxArray[(GLuint)model_01_collisionInfo[6]][1] = model_01_collisionInfo[1];
        collisionBoxArray[(GLuint)model_01_collisionInfo[6]][2] = model_01_collisionInfo[2];
        collisionBoxArray[(GLuint)model_01_collisionInfo[6]][3] = model_01_collisionInfo[3];
        collisionBoxArray[(GLuint)model_01_collisionInfo[6]][4] = model_01_collisionInfo[4];
        collisionBoxArray[(GLuint)model_01_collisionInfo[6]][5] = model_01_collisionInfo[5];        
        //=================================================================================
        collisionBoxArray[(GLuint)model_02_collisionInfo[6]][0] = model_02_collisionInfo[0];
        collisionBoxArray[(GLuint)model_02_collisionInfo[6]][1] = model_02_collisionInfo[1];
        collisionBoxArray[(GLuint)model_02_collisionInfo[6]][2] = model_02_collisionInfo[2];
        collisionBoxArray[(GLuint)model_02_collisionInfo[6]][3] = model_02_collisionInfo[3];
        collisionBoxArray[(GLuint)model_02_collisionInfo[6]][4] = model_02_collisionInfo[4];
        collisionBoxArray[(GLuint)model_02_collisionInfo[6]][5] = model_02_collisionInfo[5];      
        //=================================================================================
        collisionBoxArray[(GLuint)model_03_collisionInfo[6]][0] = model_03_collisionInfo[0];
        collisionBoxArray[(GLuint)model_03_collisionInfo[6]][1] = model_03_collisionInfo[1];
        collisionBoxArray[(GLuint)model_03_collisionInfo[6]][2] = model_03_collisionInfo[2];
        collisionBoxArray[(GLuint)model_03_collisionInfo[6]][3] = model_03_collisionInfo[3];
        collisionBoxArray[(GLuint)model_03_collisionInfo[6]][4] = model_03_collisionInfo[4];
        collisionBoxArray[(GLuint)model_03_collisionInfo[6]][5] = model_03_collisionInfo[5];        
        //=================================================================================
        collisionBoxArray[(GLuint)model_04_collisionInfo[6]][0] = model_04_collisionInfo[0];
        collisionBoxArray[(GLuint)model_04_collisionInfo[6]][1] = model_04_collisionInfo[1];
        collisionBoxArray[(GLuint)model_04_collisionInfo[6]][2] = model_04_collisionInfo[2];
        collisionBoxArray[(GLuint)model_04_collisionInfo[6]][3] = model_04_collisionInfo[3];
        collisionBoxArray[(GLuint)model_04_collisionInfo[6]][4] = model_04_collisionInfo[4];
        collisionBoxArray[(GLuint)model_04_collisionInfo[6]][5] = model_04_collisionInfo[5];         
        //=================================================================================        
        //==========================_UPDATE_COLLISION_ARRAY_USING_MODEL_POSITION__====================================================================       
     
       
       
                                
                
           
                
                 
                
                //==============================================================
                //model_01_POSITION[2] += model_01_VELOCITY[2];
                
                //====================================================================================================================================
                
                
                //====================================================================================================================================
        
                //====================================================================================================================================
                if(model_02_POSITION[0] > 11.5 || model_02_POSITION[0] < -11.5)
                {                         
                        model_02_VELOCITY[0] *= -1.0;
                }        
                if(model_02_POSITION[1] > 6.5 || model_02_POSITION[1] < -6.5)
                {                         
                        model_02_VELOCITY[1] *= -1.0;
                }          
                if(model_02_POSITION[2] > 11.5 || model_02_POSITION[2] < -11.5)
                {                         
                        model_02_VELOCITY[2] *= -1.0;
                }         
                //====================================================================================================================================
                if(model_03_POSITION[0] > 11.5 || model_03_POSITION[0] < -11.5)
                {                         
                        model_03_VELOCITY[0] *= -1.0;
                }        
                if(model_03_POSITION[1] > 6.5 || model_03_POSITION[1] < -6.5)
                {                         
                        model_03_VELOCITY[1] *= -1.0;
                }          
                if(model_03_POSITION[2] > 11.5 || model_03_POSITION[2] < -11.5)
                {                         
                        model_03_VELOCITY[2] *= -1.0;
                }         
                //====================================================================================================================================           
                if(model_04_POSITION[0] > 11.5 || model_04_POSITION[0] < -11.5)
                {                         
                        model_04_VELOCITY[0] *= -1.0;
                }        
                if(model_04_POSITION[1] > 11.5 || model_04_POSITION[1] < -11.5)
                {                         
                        model_04_VELOCITY[1] *= -1.0;
                }          
                if(model_04_POSITION[2] > 11.5 || model_04_POSITION[2] < -11.5)
                {                         
                        model_04_VELOCITY[2] *= -1.0;
                }         
                //====================================================================================================================================        
        
        
        //=======================================================================================================================
        glClearColor( 0.0f, 0.0f, 0.0f, 1.0 );
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        //----------------------------------------------------------------------------------
               
                //-------------------------------------------------------------------------------------------------------               
                glViewport(0, 0, (GLsizei)viewWidth, (GLsizei)viewHeight);
                PerspectiveMatrix(projection, fieldOfView, (GLfloat)viewWidth / (GLfloat)viewHeight, adjustNearFar[0],  adjustNearFar[1]);
                //-------------------------------------------------------------------------------------------------------          

    
        //=======================================================================================================
        shaderNumber = 26;//plastic/rubber/
        setupTransforms_MainColor();
        #include "_MODEL_FOLDERS_/flowerShield/flowerShield_Render.cpp"
        //=======================================================================================================
        shaderNumber = 26;//plastic/rubber/
        setupTransforms_MainColor();        
        Translate(modelView, model_01_POSITION[0], model_01_POSITION[1], model_01_POSITION[2]); 
        #include "_MODEL_FOLDERS_/unit_cube/unit_cube_Render.cpp"                                                                 
        //=======================================================================================================                                                                
        shaderNumber = 26;//plastic/rubber/
        setupTransforms_MainColor();        
                //====================================================================================================================================
                //====================================================================================================================================
                //====================================================================================================================================
             modelIsMovingLeft      = true;
             modelIsMovingRight     = false; 
             modelIsMovingDown      = false; 
             modelIsMovingUp        = false;          
             //------------------------ 
                CollisionTest( model_02_collisionInfo[0],  model_02_collisionInfo[1],  model_02_collisionInfo[2],  model_02_collisionInfo[3],  model_02_collisionInfo[4],  model_02_collisionInfo[5], model_02_collisionInfo[6], model_02_collisionInfo[7],  model_02_collisionInfo[8],  model_02_collisionInfo[9], model_02_collisionInfo[10], model_02_collisionInfo[11], model_02_collisionInfo[12], model_02_collisionInfo[13]);
                //--------------------------------------------------------------
                if(modelCanMoveLeft)
                {
                        model_02_POSITION[0]      += model_02_VELOCITY[0];
                        model_02_collisionInfo[0] += model_02_VELOCITY[0];
                        model_02_collisionInfo[1] += model_02_VELOCITY[0];                       
                }
                
                //====================================================================================================================================                
                       modelIsMovingLeft      = false;
                       modelIsMovingRight     = true;
                       modelIsMovingDown      = false; 
                       modelIsMovingUp        = false;
                CollisionTest(model_02_collisionInfo[0],  model_02_collisionInfo[1],  model_02_collisionInfo[2],  model_02_collisionInfo[3],  model_02_collisionInfo[4],  model_02_collisionInfo[5], model_02_collisionInfo[6], model_02_collisionInfo[7],  model_02_collisionInfo[8],  model_02_collisionInfo[9], model_02_collisionInfo[10], model_02_collisionInfo[11], model_02_collisionInfo[12], model_02_collisionInfo[13]);               
                //--------------------------------------------------------------       
                if(modelCanMoveRight)
                {
                        model_02_POSITION[0]      += model_02_VELOCITY[0]; 
                        model_02_collisionInfo[0] += model_02_VELOCITY[0];
                        model_02_collisionInfo[1] += model_02_VELOCITY[0];       
                }  
                               
                //====================================================================================================================================
                CollisionTest( model_02_collisionInfo[0],  model_02_collisionInfo[1],  model_02_collisionInfo[2],  model_02_collisionInfo[3],  model_02_collisionInfo[4],  model_02_collisionInfo[5], model_02_collisionInfo[6], model_02_collisionInfo[7],  model_02_collisionInfo[8],  model_02_collisionInfo[9], model_02_collisionInfo[10], model_02_collisionInfo[11], model_02_collisionInfo[12], model_02_collisionInfo[13]);                
                //--------------------------------------------------------------          
             modelIsMovingLeft      = false;  
             modelIsMovingRight     = false;             
             modelIsMovingDown      = true;
             modelIsMovingUp        = false;   
                if(modelCanMoveDown)
                {
                        model_02_POSITION[1]      += model_02_VELOCITY[1]; 
                        model_02_collisionInfo[2] += model_02_VELOCITY[1];
                        model_02_collisionInfo[3] += model_02_VELOCITY[1];  
                }
               
                //====================================================================================================================================                
                CollisionTest(   model_02_collisionInfo[0],  model_02_collisionInfo[1],  model_02_collisionInfo[2],  model_02_collisionInfo[3],  model_02_collisionInfo[4],  model_02_collisionInfo[5], model_02_collisionInfo[6], model_02_collisionInfo[7],  model_02_collisionInfo[8],  model_02_collisionInfo[9], model_02_collisionInfo[10], model_02_collisionInfo[11], model_02_collisionInfo[12], model_02_collisionInfo[13]);
                //--------------------------------------------------------------
             modelIsMovingLeft      = false;  
             modelIsMovingRight     = false; 
             modelIsMovingDown      = false; 
             modelIsMovingUp        = true;
             //-------------------------
                if(modelCanMoveUp)
                {
                        model_02_POSITION[1]      += model_02_VELOCITY[1];
                        model_02_collisionInfo[2] += model_02_VELOCITY[1];
                        model_02_collisionInfo[3] += model_02_VELOCITY[1];                    
                } 
                                
                //====================================================================================================================================
                //====================================================================================================================================
                //====================================================================================================================================
                
        Translate(modelView, model_02_POSITION[0], model_02_POSITION[1], model_02_POSITION[2]);                           
        #include "_MODEL_FOLDERS_/unit_cube/unit_cube_Render.cpp"                                                                 
        //======================================================================================================= 
        shaderNumber = 26;//plastic/rubber/
        setupTransforms_MainColor();        
             
             modelIsMovingLeft      = true;
             modelIsMovingRight     = false; 
             modelIsMovingDown      = false; 
             modelIsMovingUp        = false;          
             //------------------------
                CollisionTest( model_03_collisionInfo[0],  model_03_collisionInfo[1],  model_03_collisionInfo[2],  model_03_collisionInfo[3],  model_03_collisionInfo[4],  model_03_collisionInfo[5], model_03_collisionInfo[6], model_03_collisionInfo[7],  model_03_collisionInfo[8],  model_03_collisionInfo[9], model_03_collisionInfo[10], model_03_collisionInfo[11], model_03_collisionInfo[12], model_03_collisionInfo[13]);
                //--------------------------------------------------------------
                if(modelCanMoveLeft)
                {
                        model_03_POSITION[0]      += model_03_VELOCITY[0]; 
                        model_03_collisionInfo[0] += model_03_VELOCITY[0];
                        model_03_collisionInfo[1] += model_03_VELOCITY[0];                        
                }
              
                //====================================================================================================================================
                       modelIsMovingLeft      = false;
                       modelIsMovingRight     = true;
                       modelIsMovingDown      = false; 
                       modelIsMovingUp        = false;                
                CollisionTest(model_03_collisionInfo[0],  model_03_collisionInfo[1],  model_03_collisionInfo[2],  model_03_collisionInfo[3],  model_03_collisionInfo[4],  model_03_collisionInfo[5], model_03_collisionInfo[6], model_03_collisionInfo[7],  model_03_collisionInfo[8],  model_03_collisionInfo[9], model_03_collisionInfo[10], model_03_collisionInfo[11], model_03_collisionInfo[12], model_03_collisionInfo[13]);               
                //--------------------------------------------------------------                

                if(modelCanMoveRight)
                {
                        model_03_POSITION[0]      += model_03_VELOCITY[0]; 
                        model_03_collisionInfo[0] += model_03_VELOCITY[0];
                        model_03_collisionInfo[1] += model_03_VELOCITY[0];               
                }
                //====================================================================================================================================
             modelIsMovingLeft      = false;  
             modelIsMovingRight     = false;             
             modelIsMovingDown      = true;
             modelIsMovingUp        = false;                  
                CollisionTest( model_03_collisionInfo[0],  model_03_collisionInfo[1],  model_03_collisionInfo[2],  model_03_collisionInfo[3],  model_03_collisionInfo[4],  model_03_collisionInfo[5], model_03_collisionInfo[6], model_03_collisionInfo[7],  model_03_collisionInfo[8],  model_03_collisionInfo[9], model_03_collisionInfo[10], model_03_collisionInfo[11], model_03_collisionInfo[12], model_03_collisionInfo[13]);                
                //--------------------------------------------------------------                
                if(modelCanMoveDown)
                {
                        model_03_POSITION[1]      += model_03_VELOCITY[1]; 
                        model_03_collisionInfo[2] += model_03_VELOCITY[1];
                        model_03_collisionInfo[3] += model_03_VELOCITY[1];          
                }
                //====================================================================================================================================      
                CollisionTest(   model_03_collisionInfo[0],  model_03_collisionInfo[1],  model_03_collisionInfo[2],  model_03_collisionInfo[3],  model_03_collisionInfo[4],  model_03_collisionInfo[5], model_03_collisionInfo[6], model_03_collisionInfo[7],  model_03_collisionInfo[8],  model_03_collisionInfo[9], model_03_collisionInfo[10], model_03_collisionInfo[11], model_03_collisionInfo[12], model_03_collisionInfo[13]);
                //--------------------------------------------------------------                
             modelIsMovingLeft      = false;  
             modelIsMovingRight     = false; 
             modelIsMovingDown      = false; 
             modelIsMovingUp        = true;
             //-------------------------          
                if(modelCanMoveUp)
                {
                        model_03_POSITION[1]      += model_03_VELOCITY[1]; 
                        model_03_collisionInfo[2] += model_03_VELOCITY[1];
                        model_03_collisionInfo[3] += model_03_VELOCITY[1];                 
                } 
                //====================================================================================================================================
                //====================================================================================================================================
                //====================================================================================================================================  
        Translate(modelView, model_03_POSITION[0], model_03_POSITION[1], model_03_POSITION[2]);                           
        #include "_MODEL_FOLDERS_/unit_cube/unit_cube_Render.cpp"                                                                 
        //======================================================================================================= 
        shaderNumber = 26;//plastic/rubber/
        setupTransforms_MainColor();        
                
             modelIsMovingLeft      = true;
             modelIsMovingRight     = false; 
             modelIsMovingDown      = false; 
             modelIsMovingUp        = false;          
             //------------------------
                CollisionTest( model_04_collisionInfo[0],  model_04_collisionInfo[1],  model_04_collisionInfo[2],  model_04_collisionInfo[3],  model_04_collisionInfo[4],  model_04_collisionInfo[5], model_04_collisionInfo[6], model_04_collisionInfo[7],  model_04_collisionInfo[8],  model_04_collisionInfo[9], model_04_collisionInfo[10], model_04_collisionInfo[11], model_04_collisionInfo[12], model_04_collisionInfo[13]);
                //--------------------------------------------------------------
                if(modelCanMoveLeft)
                {
                        model_04_POSITION[0]      += model_04_VELOCITY[0]; 
                        model_04_collisionInfo[0] += model_04_VELOCITY[0];
                        model_04_collisionInfo[1] += model_04_VELOCITY[0]; 
                }
                //====================================================================================================================================      
                       modelIsMovingLeft      = false;
                       modelIsMovingRight     = true;
                       modelIsMovingDown      = false; 
                       modelIsMovingUp        = false;
                CollisionTest(model_04_collisionInfo[0],  model_04_collisionInfo[1],  model_04_collisionInfo[2],  model_04_collisionInfo[3],  model_04_collisionInfo[4],  model_04_collisionInfo[5], model_04_collisionInfo[6], model_04_collisionInfo[7],  model_04_collisionInfo[8],  model_04_collisionInfo[9], model_04_collisionInfo[10], model_04_collisionInfo[11], model_04_collisionInfo[12], model_04_collisionInfo[13]);               
                //--------------------------------------------------------------                
                if(modelCanMoveRight)
                {
                        model_04_POSITION[0]      += model_04_VELOCITY[0]; 
                        model_04_collisionInfo[0] += model_04_VELOCITY[0];
                        model_04_collisionInfo[1] += model_04_VELOCITY[0];                 
                }
                //====================================================================================================================================
             modelIsMovingLeft      = false;  
             modelIsMovingRight     = false;             
             modelIsMovingDown      = true;
             modelIsMovingUp        = false;  
                CollisionTest( model_04_collisionInfo[0],  model_04_collisionInfo[1],  model_04_collisionInfo[2],  model_04_collisionInfo[3],  model_04_collisionInfo[4],  model_04_collisionInfo[5], model_04_collisionInfo[6], model_04_collisionInfo[7],  model_04_collisionInfo[8],  model_04_collisionInfo[9], model_04_collisionInfo[10], model_04_collisionInfo[11], model_04_collisionInfo[12], model_04_collisionInfo[13]);                
                //--------------------------------------------------------------                
                if(modelCanMoveDown)
                {
                        model_04_POSITION[1]      += model_04_VELOCITY[1]; 
                        model_04_collisionInfo[2] += model_04_VELOCITY[1];
                        model_04_collisionInfo[3] += model_04_VELOCITY[1];  
                }
                //====================================================================================================================================
             modelIsMovingLeft      = false;  
             modelIsMovingRight     = false; 
             modelIsMovingDown      = false; 
             modelIsMovingUp        = true;
             //-------------------------
                CollisionTest(   model_04_collisionInfo[0],  model_04_collisionInfo[1],  model_04_collisionInfo[2],  model_04_collisionInfo[3],  model_04_collisionInfo[4],  model_04_collisionInfo[5], model_04_collisionInfo[6], model_04_collisionInfo[7],  model_04_collisionInfo[8],  model_04_collisionInfo[9], model_04_collisionInfo[10], model_04_collisionInfo[11], model_04_collisionInfo[12], model_04_collisionInfo[13]);
                //--------------------------------------------------------------                
                if(modelCanMoveUp)
                {
                        model_04_POSITION[1]      += model_04_VELOCITY[1]; 
                        model_04_collisionInfo[2] += model_04_VELOCITY[1];
                        model_04_collisionInfo[3] += model_04_VELOCITY[1];                  
                }
                //====================================================================================================================================                 
                //====================================================================================================================================                           
                //====================================================================================================================================   
        Translate(modelView, model_04_POSITION[0], model_04_POSITION[1], model_04_POSITION[2]);                           
        #include "_MODEL_FOLDERS_/unit_cube/unit_cube_Render.cpp"                                                                 
        //======================================================================================================= 

        //==========================_UPDATE_COLLISION_ARRAY_USING_MODEL_POSITION__====================================================================
        //=================================================================================
        collisionBoxArray[(GLuint)model_01_collisionInfo[6]][0] = model_01_collisionInfo[0];
        collisionBoxArray[(GLuint)model_01_collisionInfo[6]][1] = model_01_collisionInfo[1];
        collisionBoxArray[(GLuint)model_01_collisionInfo[6]][2] = model_01_collisionInfo[2];
        collisionBoxArray[(GLuint)model_01_collisionInfo[6]][3] = model_01_collisionInfo[3];
        collisionBoxArray[(GLuint)model_01_collisionInfo[6]][4] = model_01_collisionInfo[4];
        collisionBoxArray[(GLuint)model_01_collisionInfo[6]][5] = model_01_collisionInfo[5];        
        //=================================================================================
        collisionBoxArray[(GLuint)model_02_collisionInfo[6]][0] = model_02_collisionInfo[0];
        collisionBoxArray[(GLuint)model_02_collisionInfo[6]][1] = model_02_collisionInfo[1];
        collisionBoxArray[(GLuint)model_02_collisionInfo[6]][2] = model_02_collisionInfo[2];
        collisionBoxArray[(GLuint)model_02_collisionInfo[6]][3] = model_02_collisionInfo[3];
        collisionBoxArray[(GLuint)model_02_collisionInfo[6]][4] = model_02_collisionInfo[4];
        collisionBoxArray[(GLuint)model_02_collisionInfo[6]][5] = model_02_collisionInfo[5];      
        //=================================================================================
        collisionBoxArray[(GLuint)model_03_collisionInfo[6]][0] = model_03_collisionInfo[0];
        collisionBoxArray[(GLuint)model_03_collisionInfo[6]][1] = model_03_collisionInfo[1];
        collisionBoxArray[(GLuint)model_03_collisionInfo[6]][2] = model_03_collisionInfo[2];
        collisionBoxArray[(GLuint)model_03_collisionInfo[6]][3] = model_03_collisionInfo[3];
        collisionBoxArray[(GLuint)model_03_collisionInfo[6]][4] = model_03_collisionInfo[4];
        collisionBoxArray[(GLuint)model_03_collisionInfo[6]][5] = model_03_collisionInfo[5];        
        //=================================================================================
        collisionBoxArray[(GLuint)model_04_collisionInfo[6]][0] = model_04_collisionInfo[0];
        collisionBoxArray[(GLuint)model_04_collisionInfo[6]][1] = model_04_collisionInfo[1];
        collisionBoxArray[(GLuint)model_04_collisionInfo[6]][2] = model_04_collisionInfo[2];
        collisionBoxArray[(GLuint)model_04_collisionInfo[6]][3] = model_04_collisionInfo[3];
        collisionBoxArray[(GLuint)model_04_collisionInfo[6]][4] = model_04_collisionInfo[4];
        collisionBoxArray[(GLuint)model_04_collisionInfo[6]][5] = model_04_collisionInfo[5];         
        //=================================================================================        
        //==========================_UPDATE_COLLISION_ARRAY_USING_MODEL_POSITION__==================================================================== 
}//_END_RenderGL()


//####################################################################################################################################################
//====================================================================================================================================================
//====================================================================================================================================================
//####################################################################################################################################################



#ifdef WIN32
void ProcessKeyboard(void)
{

   //=======================================================================================
    if (keys['D'] && !keys[VK_SHIFT])
    {
             rubber_LIGHT_POSITION_01[0]         +=  0.15;
    }
    if (keys['A'] && !keys[VK_SHIFT])
    {
             rubber_LIGHT_POSITION_01[0]         -=  0.15;
    }    
    if (keys['W'] && !keys[VK_SHIFT])
    {
             rubber_LIGHT_POSITION_01[1]         +=  0.15;
    } 
    if (keys['S'] && !keys[VK_SHIFT])
    {
             rubber_LIGHT_POSITION_01[1]         -=  0.15;
    }
    if (keys['E'] && !keys[VK_SHIFT])
    {
             rubber_LIGHT_POSITION_01[2]         +=  0.15;
    }
    if (keys['Q'] && !keys[VK_SHIFT])  
    {
             rubber_LIGHT_POSITION_01[2]         -=  0.15;
    }
   //=======================================================================================

    //--------------------------------------------------------------------------
    if (keys['X'])
    {
            //shininess_hardShinyBumpPlastic                       +=  1.1;
    }
    if (keys['Z'])
    {
            //shininess_hardShinyBumpPlastic                       -=  1.1;
    }
    if (keys['M'])
    {
             //ambient_hardShinyBumpPlastic                    +=  0.01;
    }
    if (keys['N'])
    {
             //ambient_hardShinyBumpPlastic                    -=  0.01;
    }      
    //==================================================================================================================================
 
  
    if(keys[VK_F8])
    {
         ofstream outSettings("settings.cpp");
             

         outSettings << "var           model_01_POSITION[]      =  {"   
                                    << model_01_POSITION[0]     << ", "
                                    << model_01_POSITION[1]     << ", "
                                    << model_01_POSITION[2]     << ", 0.0};\n";                
         //------------------------------------------------------------------------------------------------------------------------------
         outSettings << "var           lookAt[]        =  {"   
                                    << lookAt[0]       << ", "
                                    << lookAt[1]       << ", "
                                    << lookAt[2]       << ", 0.0};\n\n\n";             
         //------------------------------------------------------------------------------------------------------------------------------
   
         outSettings << "boxCount =  " <<  boxCount <<  "\n\n";             
         //------------------------------------------------------------------------------------
         outSettings << "model_01_collisionInfo[0]   =  " <<  model_01_collisionInfo[0] <<  "\n";             
         outSettings << "model_01_collisionInfo[1]   =  " <<  model_01_collisionInfo[1] <<  "\n";      
         outSettings << "model_01_collisionInfo[2]   =  " <<  model_01_collisionInfo[2] <<  "\n";             
         outSettings << "model_01_collisionInfo[3]   =  " <<  model_01_collisionInfo[3] <<  "\n";      
         outSettings << "model_01_collisionInfo[4]   =  " <<  model_01_collisionInfo[4] <<  "\n";             
         outSettings << "model_01_collisionInfo[5]   =  " <<  model_01_collisionInfo[5] <<  "\n";   
         outSettings << "model_01_collisionInfo[6]   =  " <<  model_01_collisionInfo[6] <<  "\n\n";          
         //------------------------------------------------------------------------------------
         outSettings << "collisionBoxArray[0][0]    =  " <<  collisionBoxArray[0][0] <<  "\n";             
         outSettings << "collisionBoxArray[0][1]    =  " <<  collisionBoxArray[0][1] <<  "\n";      
         outSettings << "collisionBoxArray[0][2]    =  " <<  collisionBoxArray[0][2] <<  "\n";             
         outSettings << "collisionBoxArray[0][3]    =  " <<  collisionBoxArray[0][3] <<  "\n";      
         outSettings << "collisionBoxArray[0][4]    =  " <<  collisionBoxArray[0][4] <<  "\n";             
         outSettings << "collisionBoxArray[0][5]    =  " <<  collisionBoxArray[0][5] <<  "\n";   
         outSettings << "collisionBoxArray[0][6]    =  " <<  collisionBoxArray[0][6] <<  "\n//---------------------------------------------\n";    
         //------------------------------------------------------------------------------------
         outSettings << "model_02_collisionInfo[0]   =  " <<  model_02_collisionInfo[0] <<  "\n";             
         outSettings << "model_02_collisionInfo[1]   =  " <<  model_02_collisionInfo[1] <<  "\n";      
         outSettings << "model_02_collisionInfo[2]   =  " <<  model_02_collisionInfo[2] <<  "\n";             
         outSettings << "model_02_collisionInfo[3]   =  " <<  model_02_collisionInfo[3] <<  "\n";      
         outSettings << "model_02_collisionInfo[4]   =  " <<  model_02_collisionInfo[4] <<  "\n";             
         outSettings << "model_02_collisionInfo[5]   =  " <<  model_02_collisionInfo[5] <<  "\n";   
         outSettings << "model_02_collisionInfo[6]   =  " <<  model_02_collisionInfo[6] <<  "\n\n";          
         //------------------------------------------------------------------------------------         
         outSettings << "collisionBoxArray[1][0]    =  " <<  collisionBoxArray[1][0] <<  "\n";             
         outSettings << "collisionBoxArray[1][1]    =  " <<  collisionBoxArray[1][1] <<  "\n";      
         outSettings << "collisionBoxArray[1][2]    =  " <<  collisionBoxArray[1][2] <<  "\n";             
         outSettings << "collisionBoxArray[1][3]    =  " <<  collisionBoxArray[1][3] <<  "\n";      
         outSettings << "collisionBoxArray[1][4]    =  " <<  collisionBoxArray[1][4] <<  "\n";             
         outSettings << "collisionBoxArray[1][5]    =  " <<  collisionBoxArray[1][5] <<  "\n";   
         outSettings << "collisionBoxArray[1][6]    =  " <<  collisionBoxArray[1][6] <<  "\n//------------------------------------------------\n";    
         //------------------------------------------------------------------------------------         
         outSettings << "model_03_collisionInfo[0]   =  " <<  model_03_collisionInfo[0] <<  "\n";             
         outSettings << "model_03_collisionInfo[1]   =  " <<  model_03_collisionInfo[1] <<  "\n";      
         outSettings << "model_03_collisionInfo[2]   =  " <<  model_03_collisionInfo[2] <<  "\n";             
         outSettings << "model_03_collisionInfo[3]   =  " <<  model_03_collisionInfo[3] <<  "\n";      
         outSettings << "model_03_collisionInfo[4]   =  " <<  model_03_collisionInfo[4] <<  "\n";             
         outSettings << "model_03_collisionInfo[5]   =  " <<  model_03_collisionInfo[5] <<  "\n";   
         outSettings << "model_03_collisionInfo[6]   =  " <<  model_03_collisionInfo[6] <<  "\n\n";          
         //------------------------------------------------------------------------------------         
         outSettings << "collisionBoxArray[2][0]    =  " <<  collisionBoxArray[2][0] <<  "\n";             
         outSettings << "collisionBoxArray[2][1]    =  " <<  collisionBoxArray[2][1] <<  "\n";      
         outSettings << "collisionBoxArray[2][2]    =  " <<  collisionBoxArray[2][2] <<  "\n";             
         outSettings << "collisionBoxArray[2][3]    =  " <<  collisionBoxArray[2][3] <<  "\n";      
         outSettings << "collisionBoxArray[2][4]    =  " <<  collisionBoxArray[2][4] <<  "\n";             
         outSettings << "collisionBoxArray[2][5]    =  " <<  collisionBoxArray[2][5] <<  "\n";   
         outSettings << "collisionBoxArray[2][6]    =  " <<  collisionBoxArray[2][6] <<  "\n//------------------------------------------------\n";    
         //------------------------------------------------------------------------------------         
         outSettings << "model_04_collisionInfo[0]   =  " <<  model_04_collisionInfo[0] <<  "\n";             
         outSettings << "model_04_collisionInfo[1]   =  " <<  model_04_collisionInfo[1] <<  "\n";      
         outSettings << "model_04_collisionInfo[2]   =  " <<  model_04_collisionInfo[2] <<  "\n";             
         outSettings << "model_04_collisionInfo[3]   =  " <<  model_04_collisionInfo[3] <<  "\n";      
         outSettings << "model_04_collisionInfo[4]   =  " <<  model_04_collisionInfo[4] <<  "\n";             
         outSettings << "model_04_collisionInfo[5]   =  " <<  model_04_collisionInfo[5] <<  "\n";   
         outSettings << "model_04_collisionInfo[6]   =  " <<  model_04_collisionInfo[6] <<  "\n\n";          
         //------------------------------------------------------------------------------------         
         outSettings << "collisionBoxArray[3][0]    =  " <<  collisionBoxArray[3][0] <<  "\n";             
         outSettings << "collisionBoxArray[3][1]    =  " <<  collisionBoxArray[3][1] <<  "\n";      
         outSettings << "collisionBoxArray[3][2]    =  " <<  collisionBoxArray[3][2] <<  "\n";             
         outSettings << "collisionBoxArray[3][3]    =  " <<  collisionBoxArray[3][3] <<  "\n";      
         outSettings << "collisionBoxArray[3][4]    =  " <<  collisionBoxArray[3][4] <<  "\n";             
         outSettings << "collisionBoxArray[3][5]    =  " <<  collisionBoxArray[3][5] <<  "\n";   
         outSettings << "collisionBoxArray[3][6]    =  " <<  collisionBoxArray[3][6] <<  "\n\n";    
         //------------------------------------------------------------------------------------          
        
        
         
    }
    if (keys['R'] && R_keyIsReset)
    {      
          exitCollisionTest = true;
          animateSet = true;
          R_keyIsReset = false;
    }
    if (!keys['R'] && !R_keyIsReset)
    {      
          R_keyIsReset = true;
    }     
    //====================================================================================================================================
    if (keys[VK_LEFT])
    {
             modelIsMovingLeft      = true;
             modelIsMovingRight     = false; 
             modelIsMovingDown      = false; 
             modelIsMovingUp        = false;          
             //------------------------
             CollisionTest(model_01_collisionInfo[0],  model_01_collisionInfo[1], 
                               model_01_collisionInfo[2],  model_01_collisionInfo[3], 
                               model_01_collisionInfo[4],  model_01_collisionInfo[5], 
                               model_01_collisionInfo[6],
                               model_01_collisionInfo[7],  model_01_collisionInfo[8],  model_01_collisionInfo[9],
                               model_01_collisionInfo[10], model_01_collisionInfo[11], model_01_collisionInfo[12],
                               model_01_collisionInfo[13]
                               );                             
             
             
             if(modelCanMoveLeft)
             {
                     model_01_POSITION[0]      -= 0.2;
                     model_01_collisionInfo[0] -= 0.2;  //_0_AND_1_ARE_THE_LEFT_AND_RIGHT_BOUNDARIES
                     model_01_collisionInfo[1] -= 0.2;   //_0_AND_1_ARE_THE_LEFT_AND_RIGHT_BOUNDARIES   
             } 
           
             
     }  
    //========================================================================================================================
    if (keys[VK_RIGHT])
    {
                       modelIsMovingLeft      = false;
                       modelIsMovingRight     = true;
                       modelIsMovingDown      = false; 
                       modelIsMovingUp        = false; 
             //-----------------------------
             CollisionTest(model_01_collisionInfo[0],  model_01_collisionInfo[1], 
                                model_01_collisionInfo[2],  model_01_collisionInfo[3], 
                                model_01_collisionInfo[4],  model_01_collisionInfo[5], 
                                model_01_collisionInfo[6],
                                model_01_collisionInfo[7],  model_01_collisionInfo[8],  model_01_collisionInfo[9],
                                model_01_collisionInfo[10], model_01_collisionInfo[11], model_01_collisionInfo[12],
                                model_01_collisionInfo[13]
                                );                             
             
          
             if(modelCanMoveRight)
             {
                     model_01_POSITION[0]      += 0.2;
                     model_01_collisionInfo[0] += 0.2; //_0_AND_1_ARE_THE_LEFT_AND_RIGHT_BOUNDARIES
                     model_01_collisionInfo[1] += 0.2;  //_0_AND_1_ARE_THE_LEFT_AND_RIGHT_BOUNDARIES                    
             }
                                
    }  
    //========================================================================================================================
    if (keys[VK_DOWN])
    {
             modelIsMovingLeft      = false;  
             modelIsMovingRight     = false;             
             modelIsMovingDown      = true;
             modelIsMovingUp        = false;             
             //---------------------------
             CollisionTest(model_01_collisionInfo[0],  model_01_collisionInfo[1], 
                               model_01_collisionInfo[2],  model_01_collisionInfo[3], 
                               model_01_collisionInfo[4],  model_01_collisionInfo[5], 
                               model_01_collisionInfo[6],
                               model_01_collisionInfo[7],  model_01_collisionInfo[8],  model_01_collisionInfo[9],
                               model_01_collisionInfo[10], model_01_collisionInfo[11], model_01_collisionInfo[12],
                               model_01_collisionInfo[13]
                               );                              
             
           
             if(modelCanMoveDown)
             {
                     model_01_POSITION[1]      -= 0.2;
                     model_01_collisionInfo[2] -= 0.2; //_2_AND_3_ARE_THE_BOTTOM_AND_TOP_BOUNDARIES
                     model_01_collisionInfo[3] -= 0.2; //_2_AND_3_ARE_THE_BOTTOM_AND_TOP_BOUNDARIES
             }
                                
    }  
    //========================================================================================================================
    if (keys[VK_UP])
    {
             modelIsMovingLeft      = false;  
             modelIsMovingRight     = false; 
             modelIsMovingDown      = false; 
             modelIsMovingUp        = true;
             //-------------------------
             CollisionTest(  model_01_collisionInfo[0],  model_01_collisionInfo[1], 
                               model_01_collisionInfo[2],  model_01_collisionInfo[3], 
                               model_01_collisionInfo[4],  model_01_collisionInfo[5], 
                               model_01_collisionInfo[6],
                               model_01_collisionInfo[7],  model_01_collisionInfo[8],  model_01_collisionInfo[9],
                               model_01_collisionInfo[10], model_01_collisionInfo[11], model_01_collisionInfo[12],
                               model_01_collisionInfo[13]
                               );                               
             
             if(modelCanMoveUp)
             {
                     model_01_POSITION[1]      += 0.2;
                     model_01_collisionInfo[2] += 0.2; //_2_AND_3_ARE_THE_BOTTOM_AND_TOP_BOUNDARIES
                     model_01_collisionInfo[3] += 0.2; //_2_AND_3_ARE_THE_BOTTOM_AND_TOP_BOUNDARIES
             }
                              
    }  
    //========================================================================================================================

}//_END_ProcessKeyboard()
#endif


void configureMovementSwitches(bool left, bool right, bool up, bool down, bool far, bool near)
{
         
}


//####################################################################################################################################################
//====================================================================================================================================================
//====================================================================================================================================================
//####################################################################################################################################################

void CollisionTest(     GLfloat leftEdge,           GLfloat rightEdge, 
                        GLfloat bottomEdge,         GLfloat topEdge, 
                        GLfloat farEdge,            GLfloat nearEdge, 
                        GLfloat model_ID,   
                        GLfloat velocity_X,         GLfloat velocity_Y,     GLfloat velocity_Z,
                        GLfloat bounceFactor_X,     GLfloat bounceFactor_Y, GLfloat bounceFactor_Z,
                        GLfloat updateCollisionInfo
                      )
{       //=========================================================================================
        modelCanMoveLeft   = true;
        modelCanMoveRight  = true;
        modelCanMoveDown   = true;
        modelCanMoveUp     = true;        
        boxCollisionHasOccured = false;
        
        for(int i = 0; i < boxCount; i++)
        {       
                //==================================================
                if(exitCollisionTest)//diagnostics-> key 'R'
                {
                     exitCollisionTest = false;
                     break;
                }
                //==========================================================================================
                if((leftEdge  <= collisionBoxArray[i][1] && rightEdge >= collisionBoxArray[i][0]) 
                || (rightEdge >= collisionBoxArray[i][0] && leftEdge  <= collisionBoxArray[i][1]))
                {
                        if(topEdge >= collisionBoxArray[i][2] && bottomEdge <= collisionBoxArray[i][3])
                        {
                                //if(nearEdge >= collisionBoxArray[i][4] && farEdge <= collisionBoxArray[i][5])
                                //{
                                        
                                        boxCollisionHasOccured = true;      
                                //}
                        }
                }
                if(model_ID == collisionBoxArray[i][6])
                {
                      boxCollisionHasOccured = false;              
                }                

                
                //================================================
                if(boxCollisionHasOccured == true)
                {
                        if(modelIsMovingLeft)
                        {
                                modelCanMoveLeft = false;    
                               break;
                        }
                        if(modelIsMovingRight)
                        {
                                modelCanMoveRight = false;    
                                
                                
                                break;
                        }                        
                        if(modelIsMovingDown)
                        {
                                modelCanMoveDown = false;    
                                
                                
                                break;
                        }
                        if(modelIsMovingUp)
                        {
                                modelCanMoveUp = false;    
                                
                                
                                break;
                        }
                        modelIsMovingLeft      = false;  
                        modelIsMovingRight     = false; 
                        modelIsMovingDown      = false; 
                        modelIsMovingUp        = false; 
                                                 
                        
                }
                
        } 
        
}

//####################################################################################################################################################
//====================================================================================================================================================
//====================================================================================================================================================
//####################################################################################################################################################


void shutDownGL( void )
{
     #include "_MODEL_FOLDERS_/unit_cube/unit_cube_Shutdown.cpp"                                                               
     //====================================================================================  
  
   
}



