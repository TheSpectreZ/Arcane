#pragma once
#include <utility>

#include "Core/Type.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "api/glcorearb.h"
#include "api/glext.h"
#include "api/wglext.h"

#define GL_FUNC_LIST \
    /* Error */ \
    X(PFNGLGETERRORPROC, GetError) \
    /* Clearing */ \
    X(PFNGLCLEARPROC, Clear) \
    X(PFNGLCLEARCOLORPROC, ClearColor) \
    X(PFNGLCLEARDEPTHPROC, ClearDepth) \
    /* Viewport */ \
    X(PFNGLVIEWPORTPROC, Viewport) \
    /* Enable / Disable */ \
    X(PFNGLENABLEPROC, Enable) \
    X(PFNGLDISABLEPROC, Disable) \
    X(PFNGLBLENDFUNCPROC, BlendFunc) \
    X(PFNGLDEPTHFUNCPROC, DepthFunc) \
    /* Drawing */ \
    X(PFNGLDRAWELEMENTSPROC, DrawElements) \
    X(PFNGLDRAWARRAYSPROC, DrawArrays) \
    /* Buffers */ \
    X(PFNGLGENBUFFERSPROC, GenBuffers) \
    X(PFNGLBINDBUFFERPROC, BindBuffer) \
    X(PFNGLBUFFERDATAPROC, BufferData) \
    X(PFNGLDELETEBUFFERSPROC, DeleteBuffers) \
    /* Vertex attributes */ \
    X(PFNGLVERTEXATTRIBPOINTERPROC, VertexAttribPointer) \
    X(PFNGLENABLEVERTEXATTRIBARRAYPROC, EnableVertexAttribArray) \
    X(PFNGLDISABLEVERTEXATTRIBARRAYPROC, DisableVertexAttribArray) \
    /* Shaders */ \
    X(PFNGLCREATESHADERPROC, CreateShader) \
    X(PFNGLSHADERSOURCEPROC, ShaderSource) \
    X(PFNGLCOMPILESHADERPROC, CompileShader) \
    X(PFNGLCREATEPROGRAMPROC, CreateProgram) \
    X(PFNGLATTACHSHADERPROC, AttachShader) \
    X(PFNGLLINKPROGRAMPROC, LinkProgram) \
    X(PFNGLUSEPROGRAMPROC, UseProgram) \
    X(PFNGLGETSHADERIVPROC, GetShaderiv) \
    X(PFNGLGETSHADERINFOLOGPROC, GetShaderInfoLog) \
    X(PFNGLGETPROGRAMIVPROC, GetProgramiv) \
    X(PFNGLGETPROGRAMINFOLOGPROC, GetProgramInfoLog) \
    X(PFNGLDELETEPROGRAMPROC, DeleteProgram) \
    X(PFNGLDELETESHADERPROC, DeleteShader) \
    X(PFNGLGETUNIFORMLOCATIONPROC, GetUniformLocation) \
    X(PFNGLUNIFORM1IPROC, Uniform1i) \
    X(PFNGLUNIFORM1FPROC, Uniform1f) \
    X(PFNGLUNIFORM3FVPROC, Uniform3fv) \
    X(PFNGLUNIFORM4FVPROC, Uniform4fv) \
    X(PFNGLUNIFORMMATRIX4FVPROC, UniformMatrix4fv) \
    /* Textures */ \
    X(PFNGLGENTEXTURESPROC, GenTextures) \
    X(PFNGLBINDTEXTUREPROC, BindTexture) \
    X(PFNGLTEXPARAMETERIPROC, TexParameteri) \
    X(PFNGLTEXIMAGE2DPROC, TexImage2D) \
    X(PFNGLDELETETEXTURESPROC, DeleteTextures)

namespace arc
{
	std::pair<i32, PIXELFORMATDESCRIPTOR> GetOpenGLPixelFormat();
	void LoadOpenGLFunctions();
}

namespace gl
{

#define X(type, name) static type name = nullptr;
    GL_FUNC_LIST
#undef X

}