#include <QDebug>
#include <QGuiApplication>
#include <QOffscreenSurface>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>
#include <QOpenGLVersionProfile>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    qputenv("QT_QPA_PLATFORM", "offscreen");
    QGuiApplication app(argc, argv);

    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    const QOpenGLVersionProfile profile(format);
    if (!profile.isValid() || profile.version() != qMakePair(3, 3) ||
        profile.profile() != QSurfaceFormat::CoreProfile)
    {
        return 1;
    }

    QOpenGLFramebufferObjectFormat fboFormat;
    fboFormat.setSamples(4);
    fboFormat.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    if (fboFormat.samples() != 4 ||
        fboFormat.attachment() != QOpenGLFramebufferObject::CombinedDepthStencil)
    {
        return 1;
    }

    QOpenGLContext context;
    if (!context.create())
    {
        qDebug() << "no OpenGL context available, skipping buffer test";
        return 0;
    }
    QOffscreenSurface surface;
    surface.setFormat(context.format());
    surface.create();
    if (!context.makeCurrent(&surface))
    {
        return 1;
    }
    QOpenGLBuffer buffer(QOpenGLBuffer::VertexBuffer);
    if (!buffer.create() || !buffer.bind())
    {
        return 1;
    }
    const float vertices[] = {0, 0, 1, 0, 0, 1};
    buffer.allocate(vertices, sizeof(vertices));
    const bool sizeMatches = buffer.size() == int(sizeof(vertices));
    buffer.destroy();
    context.doneCurrent();
    return sizeMatches ? 0 : 1;
}
