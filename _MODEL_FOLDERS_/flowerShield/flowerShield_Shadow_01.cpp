      
       
       //----------------------------------------------------------------------------------------
       Translate(LightModelViewMatrix, flowerShield_POSITION[0] * scaleMoveShadows[0], 
                                       flowerShield_POSITION[1] * scaleMoveShadows[1], 
                                       flowerShield_POSITION[2] * scaleMoveShadows[2]);                                                                                         
       //----------------------------------------------------------------------------------------       
       Rotate(LightModelViewMatrix,    flowerShield_ROTATE[0], 
                                       flowerShield_ROTATE[1], 
                                       flowerShield_ROTATE[2], 
                                       flowerShield_ROTATE[3]);          

       //=================================================================================================================   
       glBindBuffer(GL_ARRAY_BUFFER, flowerShield_VBO);                                                                                                                                
       glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, flowerShield_INDEX_VBO);       


//=================================================================================================================         
SelectShader(shaderNumber);
//=================================================================================================================
                                                                                                                                           
                                                                                                                           
    //----------------------------------------------------           
    glDrawElements(GL_TRIANGLES, 120, GL_UNSIGNED_INT, 0);
