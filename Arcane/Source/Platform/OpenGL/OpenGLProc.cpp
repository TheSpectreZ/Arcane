#include "OpenGLProc.h"

#define STR_CAT_IMPL(a, b) a##b
#define STR_CAT(a, b) STR_CAT_IMPL(a, b)

namespace gl
{
	static i32 PixelFormat = 0;
	static PIXELFORMATDESCRIPTOR FormatDescriptor;

	template<typename T>
	T LoadGLProc(const char* name)
	{
		T proc = reinterpret_cast<T>(wglGetProcAddress(name));
		if (!proc)
		{
			static HMODULE module = LoadLibraryA("opengl32.dll");
			proc = reinterpret_cast<T>(GetProcAddress(module, name));
		}
		return proc;
	}

	static void LoadFuncProc()
	{
#define X(type, name) name = LoadGLProc<type>(STR_CAT("gl", #name));
		GetError = LoadGLProc<PFNGLGETERRORPROC>("gl""GetError"); Clear = LoadGLProc<PFNGLCLEARPROC>("gl""Clear"); ClearColor = LoadGLProc<PFNGLCLEARCOLORPROC>("gl""ClearColor"); ClearDepth = LoadGLProc<PFNGLCLEARDEPTHPROC>("gl""ClearDepth"); Viewport = LoadGLProc<PFNGLVIEWPORTPROC>("gl""Viewport"); Enable = LoadGLProc<PFNGLENABLEPROC>("gl""Enable"); Disable = LoadGLProc<PFNGLDISABLEPROC>("gl""Disable"); BlendFunc = LoadGLProc<PFNGLBLENDFUNCPROC>("gl""BlendFunc"); DepthFunc = LoadGLProc<PFNGLDEPTHFUNCPROC>("gl""DepthFunc"); DrawElements = LoadGLProc<PFNGLDRAWELEMENTSPROC>("gl""DrawElements"); DrawArrays = LoadGLProc<PFNGLDRAWARRAYSPROC>("gl""DrawArrays"); GenBuffers = LoadGLProc<PFNGLGENBUFFERSPROC>("gl""GenBuffers"); BindBuffer = LoadGLProc<PFNGLBINDBUFFERPROC>("gl""BindBuffer"); BufferData = LoadGLProc<PFNGLBUFFERDATAPROC>("gl""BufferData"); DeleteBuffers = LoadGLProc<PFNGLDELETEBUFFERSPROC>("gl""DeleteBuffers"); VertexAttribPointer = LoadGLProc<PFNGLVERTEXATTRIBPOINTERPROC>("gl""VertexAttribPointer"); EnableVertexAttribArray = LoadGLProc<PFNGLENABLEVERTEXATTRIBARRAYPROC>("gl""EnableVertexAttribArray"); DisableVertexAttribArray = LoadGLProc<PFNGLDISABLEVERTEXATTRIBARRAYPROC>("gl""DisableVertexAttribArray"); CreateShader = LoadGLProc<PFNGLCREATESHADERPROC>("gl""CreateShader"); ShaderSource = LoadGLProc<PFNGLSHADERSOURCEPROC>("gl""ShaderSource"); CompileShader = LoadGLProc<PFNGLCOMPILESHADERPROC>("gl""CompileShader"); CreateProgram = LoadGLProc<PFNGLCREATEPROGRAMPROC>("gl""CreateProgram"); AttachShader = LoadGLProc<PFNGLATTACHSHADERPROC>("gl""AttachShader"); LinkProgram = LoadGLProc<PFNGLLINKPROGRAMPROC>("gl""LinkProgram"); UseProgram = LoadGLProc<PFNGLUSEPROGRAMPROC>("gl""UseProgram"); GetShaderiv = LoadGLProc<PFNGLGETSHADERIVPROC>("gl""GetShaderiv"); GetShaderInfoLog = LoadGLProc<PFNGLGETSHADERINFOLOGPROC>("gl""GetShaderInfoLog"); GetProgramiv = LoadGLProc<PFNGLGETPROGRAMIVPROC>("gl""GetProgramiv"); GetProgramInfoLog = LoadGLProc<PFNGLGETPROGRAMINFOLOGPROC>("gl""GetProgramInfoLog"); DeleteProgram = LoadGLProc<PFNGLDELETEPROGRAMPROC>("gl""DeleteProgram"); DeleteShader = LoadGLProc<PFNGLDELETESHADERPROC>("gl""DeleteShader"); GetUniformLocation = LoadGLProc<PFNGLGETUNIFORMLOCATIONPROC>("gl""GetUniformLocation"); Uniform1i = LoadGLProc<PFNGLUNIFORM1IPROC>("gl""Uniform1i"); Uniform1f = LoadGLProc<PFNGLUNIFORM1FPROC>("gl""Uniform1f"); Uniform3fv = LoadGLProc<PFNGLUNIFORM3FVPROC>("gl""Uniform3fv"); Uniform4fv = LoadGLProc<PFNGLUNIFORM4FVPROC>("gl""Uniform4fv"); UniformMatrix4fv = LoadGLProc<PFNGLUNIFORMMATRIX4FVPROC>("gl""UniformMatrix4fv"); GenTextures = LoadGLProc<PFNGLGENTEXTURESPROC>("gl""GenTextures"); BindTexture = LoadGLProc<PFNGLBINDTEXTUREPROC>("gl""BindTexture"); TexParameteri = LoadGLProc<PFNGLTEXPARAMETERIPROC>("gl""TexParameteri"); TexImage2D = LoadGLProc<PFNGLTEXIMAGE2DPROC>("gl""TexImage2D"); DeleteTextures = LoadGLProc<PFNGLDELETETEXTURESPROC>("gl""DeleteTextures");
#undef X
	}
}

namespace arc
{

	std::pair<i32, PIXELFORMATDESCRIPTOR> GetOpenGLPixelFormat()
	{
		return { gl::PixelFormat, gl::FormatDescriptor };
	}

	void LoadOpenGLFunctions()
	{
		WNDCLASS wc = {};
		wc.lpfnWndProc = DefWindowProc;
		wc.hInstance = GetModuleHandle(nullptr);
		wc.lpszClassName = "GLContextDummy";
		wc.style = CS_OWNDC;

		RegisterClassA(&wc);

		HWND hwnd = CreateWindowExA(0, wc.lpszClassName, "GLContextDummy",
			WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
			8, 8, nullptr, nullptr, wc.hInstance, nullptr);

		gl::FormatDescriptor =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
			PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
			32,                   // Colordepth of the framebuffer.
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,                   // Number of bits for the depthbuffer
			8,                    // Number of bits for the stencilbuffer
			0,                    // Number of Aux buffers in the framebuffer.
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		HDC hdc = GetDC(hwnd);

		gl::PixelFormat = ChoosePixelFormat(hdc, &gl::FormatDescriptor);
		SetPixelFormat(hdc, gl::PixelFormat, &gl::FormatDescriptor);

		HGLRC hglrc = wglCreateContext(hdc);
		wglMakeCurrent(hdc, hglrc);

		//

		gl::LoadFuncProc();

		//

		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(hglrc);
		ReleaseDC(hwnd, hdc);
		DestroyWindow(hwnd);
	}
}