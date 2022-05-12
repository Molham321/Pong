
#pragma once

namespace gfx
{
    typedef void* BHandle;
} // namespace gfx

namespace gfx
{
    struct SMeshInfo
    {
        float*  m_pVertices;            ///< An array with vertices, whereas each vertex is represented by 3 float values.
        float*  m_pNormals;             ///< An array with normals, whereas each normal is represented by 3 float values. Set to null if not supported.
        float*  m_pColors;              ///< An array with colors, whereas each color is represented by 4 float values. Set to null if not supported.
        float*  m_pTexCoords;           ///< An array with texture coordinates, whereas each texture coordinate is represented by 2 float values. Set to null if not supported.
        int     m_NumberOfVertices;     ///< The number of vertices in the array. If defined the number of normals, colors, and texture coordinates has to match this number.
        int*    m_pIndices;             ///< An array with indices addressing the vertices. Each sequent triple of indices represents one triangle.
        int     m_NumberOfIndices;      ///< The number of indices in the index array.
        BHandle m_pTexture;             ///< A handle to a former created texture if the mesh should be textured. Texture coordinates have to be defined in this case.
    };
} // namespace gfx

namespace gfx
{
    class IApplication
    {
        public:

            virtual ~IApplication();

        public:

            bool OnStartup();
            bool OnShutdown();
            bool OnCreateTextures();
            bool OnReleaseTextures();
            bool OnCreateMeshes();
            bool OnReleaseMeshes();
            bool OnResize(int _Width, int _Height);
            bool OnKeyEvent(unsigned int _Key, bool _IsKeyDown, bool _IsAltDown);
            bool OnMouseEvent(int _X, int _Y, int _Button, bool _IsButtonDown, bool _IsDoubleClick, int _WheelDelta);
            bool OnUpdate();
            bool OnFrame();

        private:

            virtual bool InternOnStartup();
            virtual bool InternOnShutdown();
            virtual bool InternOnCreateTextures();
            virtual bool InternOnReleaseTextures();
            virtual bool InternOnCreateMeshes();
            virtual bool InternOnReleaseMeshes();
            virtual bool InternOnResize(int _Width, int _Height);
            virtual bool InternOnKeyEvent(unsigned int _Key, bool _IsKeyDown, bool _IsAltDown);
            virtual bool InternOnMouseEvent(int _X, int _Y, int _Button, bool _IsButtonDown, bool _IsDoubleClick, int _WheelDelta);
            virtual bool InternOnUpdate();
            virtual bool InternOnFrame();
    };
} // namespace gfx

namespace gfx
{
    void RunApplication(int _Width, int _Height, const char* _pTitle, IApplication* _pApplication);
    void StopApplication();
} // namespace gfx

namespace gfx
{
    void SetClearColor(const float* _pColor);
    void SetDepthTest(bool _Flag);
    void SetWireFrame(bool _Flag);
    void SetAlphaBlending(bool _Flag);
} // namespace gfx

namespace gfx
{
    void CreateTexture(const char* _pPath, BHandle* _ppTexture);
    void ReleaseTexture(BHandle _pTexture);
} // namespace gfx

namespace gfx
{
    void CreateMesh(const SMeshInfo& _rMeshInfo, BHandle* _ppMesh);
    void ReleaseMesh(BHandle _pMesh);
} // namespace gfx

namespace gfx
{
    void DrawMesh(BHandle _pMesh);
} // namespace gfx

namespace gfx
{
    void SetWorldMatrix(const float* _pMatrix);
    void SetViewMatrix(const float* _pMatrix);
    void SetProjectionMatrix(const float* _pMatrix);
} // namespace gfx

namespace gfx
{
    void SetLightPosition(const float* _pPosition);
    void SetLightColor(const float* _pAmbientColor, const float* _pDiffuseColor, const float* _pSpecularColor, float _SpecularExponent);
} // namespace gfx

namespace gfx
{
    float GetDotProduct2D(const float* _pVector1, const float* _pVector2);
    float GetDotProduct3D(const float* _pVector1, const float* _pVector2);
    float GetDotProduct4D(const float* _pVector1, const float* _pVector2);

    float* GetCrossProduct(const float* _pVector1, const float* _pVector2, float* _pResultVector);

    float* GetNormalizedVector(const float* _pVector, float* _pResultVector);
    float* TransformVector(const float* _pVector, const float* _pMatrix, float* _pResultVector);

    float* MulMatrix(const float* _pLeftMatrix, const float* _pRightMatrix, float* _pResultMatrix);

    float* GetIdentityMatrix(float* _pResultMatrix);
    float* GetTranslationMatrix(float _X, float _Y, float _Z, float* _pResultMatrix);
    float* GetScaleMatrix(float _Scalar, float* _pResultMatrix);
    float* GetScaleMatrix(float _ScalarX, float _ScalarY, float _ScalarZ, float* _pResultMatrix);
    float* GetRotationXMatrix(float _Degrees, float* _pResultMatrix);
    float* GetRotationYMatrix(float _Degrees, float* _pResultMatrix);
    float* GetRotationZMatrix(float _Degrees, float* _pResultMatrix);

    float* GetViewMatrix(float* _pEye, float* _pAt, float* _pUp, float* _pResultMatrix);

    float* GetProjectionMatrix(float _FieldOfViewY, float _AspectRatio, float _Near, float _Far, float* _pResultMatrix);
} // namespace gfx

