/*
gl-wes-v2:  OpenGL 2.0 to OGLESv2.0 wrapper
Contact:    lachlan.ts@gmail.com
Copyright (C) 2009  Lachlan Tychsen - Smith aka Adventus

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 3 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __WES_GL_ARB_H__
#define __WES_GL_ARB_H__

#define GL_RENDERBUFFER_EXT					GL_RENDERBUFFER
#define GL_FRAMEBUFFER_EXT 					GL_FRAMEBUFFER
#define GL_COLOR_ATTACHMENT0_EXT 			GL_COLOR_ATTACHMENT0
#define GL_DEPTH_ATTACHMENT_EXT 			GL_DEPTH_ATTACHMENT
#define GL_FRAMEBUFFER_COMPLETE_EXT 		GL_FRAMEBUFFER_COMPLETE
#define GL_FRAMEBUFFER_UNSUPPORTED_EXT 		GL_FRAMEBUFFER_UNSUPPORTED
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT 			GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT 	GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT
#define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT 			GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS
#define GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT 				GL_FRAMEBUFFER_INCOMPLETE_FORMATS
#define GL_FRAMEBUFFER_BINDING_EXT 			GL_FRAMEBUFFER_BINDING
#define GL_FOG_COORDINATE_SOURCE_EXT 		GL_FOG_COORD_SRC
#define GL_FOG_COORDINATE_EXT				GL_FOG_COORD
#define GL_FOG_COORDINATE_ARRAY_EXT         GL_FOG_COORD_ARRAY
#define GL_SECONDARY_COLOR_ARRAY_EXT        GL_SECONDARY_COLOR_ARRAY


#define GL_MAX_TEXTURE_UNITS_ARB        GL_MAX_TEXTURE_UNITS
#define GL_TEXTURE0_ARB                 GL_TEXTURE0
#define GL_TEXTURE1_ARB                 GL_TEXTURE1
#define GL_TEXTURE2_ARB                 GL_TEXTURE2
#define GL_TEXTURE3_ARB                 GL_TEXTURE3


/* Tex env */
#define GL_TEXTURE_ENV_ARB                          GL_TEXTURE_ENV
#define GL_TEXTURE_ENV_MODE_ARB                     GL_TEXTURE_ENV_MODE
#define GL_TEXTURE_ENV_COLOR_ARB                    GL_TEXTURE_ENV_COLOR
#define GL_COMBINE_ARB                              GL_COMBINE
#define GL_COMBINE_RGB_ARB                          GL_COMBINE_RGB
#define GL_COMBINE_ALPHA_ARB                        GL_COMBINE_ALPHA
#define GL_SOURCE0_RGB_ARB                          GL_SOURCE0_RGB
#define GL_SOURCE1_RGB_ARB                          GL_SOURCE1_RGB
#define GL_SOURCE2_RGB_ARB                          GL_SOURCE2_RGB
#define GL_SOURCE0_ALPHA_ARB                        GL_SOURCE0_ALPHA
#define GL_SOURCE1_ALPHA_ARB                        GL_SOURCE1_ALPHA
#define GL_SOURCE2_ALPHA_ARB                        GL_SOURCE2_ALPHA
#define GL_OPERAND0_RGB_ARB                         GL_OPERAND0_RGB
#define GL_OPERAND1_RGB_ARB                         GL_OPERAND1_RGB
#define GL_OPERAND2_RGB_ARB                         GL_OPERAND2_RGB
#define GL_OPERAND0_ALPHA_ARB                       GL_OPERAND0_ALPHA
#define GL_OPERAND1_ALPHA_ARB                       GL_OPERAND1_ALPHA
#define GL_OPERAND2_ALPHA_ARB                       GL_OPERAND2_ALPHA
#define GL_ADD_SIGNED_ARB                           GL_ADD_SIGNED
#define GL_INTERPOLATE_ARB                          GL_INTERPOLATE
#define GL_SUBTRACT_ARB                             GL_SUBTRACT
#define GL_CONSTANT_ARB                             GL_CONSTANT
#define GL_PRIMARY_COLOR_ARB                        GL_PRIMARY_COLOR
#define GL_PREVIOUS_ARB                             GL_PREVIOUS
#define GL_DOT3_RGB_ARB                             GL_DOT3_RGB
#define GL_DOT3_RGBA_ARB                            GL_DOT3_RGBA


/* ATI Extensions */
#define GL_MODULATE_ADD_ATI                         0x8744
#define GL_MODULATE_SIGNED_ADD_ATI                  0x8745
#define GL_MODULATE_SUBTRACT_ATI                    0x8746

/*  Textures    */
#define GL_UNSIGNED_SHORT_4_4_4_4_EXT               GL_UNSIGNED_SHORT_4_4_4_4
#define GL_UNSIGNED_SHORT_5_5_5_1_EXT               GL_UNSIGNED_SHORT_5_5_5_1
#define GL_UNSIGNED_SHORT_5_6_5_EXT                 GL_UNSIGNED_SHORT_5_6_5

/* Shaders */
#define GL_FRAGMENT_SHADER_ARB                  	GL_FRAGMENT_SHADER
#define GL_VERTEX_SHADER_ARB                     	GL_VERTEX_SHADER
#define GL_OBJECT_LINK_STATUS_ARB	                GL_OBJECT_LINK_STATUS


//ARB / EXT Wrappers:
#define glFogCoordPointerEXT            glFogCoordPointer
#define glClientActiveTextureARB        glClientActiveTexture
#define glSecondaryColorPointerEXT      glSecondaryColorPointer
#define glActiveTextureARB  		    glActiveTexture
#define glBindFramebufferEXT  		    glBindFramebuffer
#define glBindRenderbufferEXT 		    glBindRenderbuffer
#define glFramebufferTexture2DEXT 	    glFramebufferTexture2D
#define glFramebufferRenderbufferEXT    glFramebufferRenderbuffer
#define glCheckFramebufferStatusEXT     glCheckFramebufferStatus
#define glDeleteFramebuffersEXT 	    glDeleteFramebuffers
#define glDeleteRenderbuffersEXT	    glDeleteRenderbuffers
#define glGenFramebuffersEXT		    glGenFramebuffers
#define glGenRenderbuffersEXT		    glGenRenderbuffers
#define glRenderbufferStorageEXT 	    glRenderbufferStorage
#define glBlendFuncSeparateEXT		    glBlendFuncSeparate
#define glSecondaryColor3fvEXT          glSecondaryColor3fv
#define glSecondaryColor3fEXT           glSecondaryColor3f

#define glMultiTexCoord2fARB        glMultiTexCoord2f
#define glCompressedTexImage2DARB   glCompressedTexImage2D
#define glCreateShaderObjectARB		glCreateShader
#define glShaderSourceARB			glShaderSource
#define glCompileShaderARB			glCompileShader
#define glCreateProgramObjectARB	glCreateProgram
#define glAttachObjectARB			glAttachShader
#define glLinkProgramARB 			glLinkProgram
#define glUseProgramObjectARB		glUseProgram


#define glGetUniformLocationARB		glGetUniformLocation
#define glUniform1iARB				glUniform1i
#define glUniform4fARB				glUniform4f
#define glUniform1fARB				glUniform1f
#define GLhandleARB					GLint


/* N64 Extensions               */
#define GL_TEXSCALE_N64             0xFF00
#define GL_TEXOFFSET_N64            0xFF01
#define GL_CACHESCALE_N64           0xFF02
#define GL_CACHESHIFTSCALE_N64      0xFF03
#define GL_CACHEOFFSET_N64          0xFF04

#define GL_TEXGEN_N64               0xFF05
#define GL_ZPRIM_N64                0xFF06
#define GL_FOG_N64                  0xFF07

#define GL_COLORALPHA_ARRAY_N64     0xFF08

#define GL_FOG_MULTIPLIER_N64       0xFF09
#define GL_FOG_OFFSET_N64           0xFF0A

#endif