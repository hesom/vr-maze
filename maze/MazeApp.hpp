/*
 * Copyright (C) 2016, 2017 Computer Graphics Group, University of Siegen
 * Written by Martin Lambers <martin.lambers@uni-siegen.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef QVR_EXAMPLE_OPENGL_MINIMAL_HPP
#define QVR_EXAMPLE_OPENGL_MINIMAL_HPP

#include <QOpenGLShaderProgram>
#include <QElapsedTimer>

#include <qvr/app.hpp>
#include <qvr/device.hpp>

enum class GridCell : int
{
    EMPTY,
    WALL,
    FINISH,
    SPAWN
};

class MazeApp : public QVRApp
{
private:
    /* Data not directly relevant for rendering */
    bool _wantExit;             // do we want to exit the app?
    QElapsedTimer _timer;       // used for rotating the box

    /* Static data for rendering, initialized per process. */
    unsigned int _fbo;          // Framebuffer object to render into
    unsigned int _fboDepthTex;  // Depth attachment for the FBO
    unsigned int _vaoWall;          // Vertex array object for the box
    unsigned int _vaoIndicesWall;   // Number of indices to render for the box
    unsigned int _vaoFloor;
    unsigned int _vaoIndicesFloor;
    QOpenGLShaderProgram _prg;  // Shader program for rendering
    GridCell* mazeGrid;    // 0 = nothing, 1 = wall, 2 = finish, (3 = spawn)
    size_t gridWidth;
    size_t gridHeight;

    /* Dynamic data for rendering. Needs to be serialized. */
    float _rotationAngle;       // animated box rotation

public:
    MazeApp();

    // override functions 
    bool initProcess(QVRProcess* p) override;

    void render(QVRWindow* w, const QVRRenderContext& c, const unsigned int* textures) override;

    void update(const QList<QVRObserver*>& observers) override;

    bool wantExit() override;

    void serializeDynamicData(QDataStream& ds) const override;
    void deserializeDynamicData(QDataStream& ds) override;

    void keyPressEvent(const QVRRenderContext& context, QKeyEvent* event) override;

    void exitProcess(QVRProcess* p) override;


    // custom functions
    GridCell GetCell(int row, int col)
    {
        return mazeGrid[row * gridWidth + col];
    }
};

#endif
