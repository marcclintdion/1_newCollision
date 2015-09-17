glBindBuffer(GL_ARRAY_BUFFER, flowerShield_VBO);                                                                                                                                
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, flowerShield_INDEX_VBO);       
//=========================================================================================
     
        Translate(modelView, flowerShield_POSITION[0], 
                             flowerShield_POSITION[1], 
                             flowerShield_POSITION[2]);
        //----------------------------------------------------------------------                                                                                                             
        Rotate(modelView,    flowerShield_ROTATE[0], 
                             flowerShield_ROTATE[1],
                             flowerShield_ROTATE[2], 
                             flowerShield_ROTATE[3]);   

//=================================================================================================================         
SelectShader(shaderNumber);
//=================================================================================================================
                                                                                                               
    //---               
    glActiveTexture ( GL_TEXTURE1 );                                                                                                                                          
    glBindTexture(GL_TEXTURE_2D, flowerShield_NORMALMAP);                                                                                                                          
    //---                                                                                                                                                                     
    glActiveTexture (GL_TEXTURE0);                                                                                                                                            
    glBindTexture(GL_TEXTURE_2D, flowerShield_TEXTUREMAP);                                                                                                                            
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__DRAW              
    glDrawElements(GL_TRIANGLES, 120, GL_UNSIGNED_INT, 0);
