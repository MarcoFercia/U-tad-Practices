
#include <vector>

class Buffer;
class Shader;

class Mesh
{
public:

    Mesh();
    ~Mesh();
private:

    std::vector<Buffer*> bufferVector;
    std::vector<Shader*> ShaderVector;

public:
    void addBuffer(Buffer* _buffer, Shader* _shader = nullptr);
    size_t getNumBuffers() const;
    const Buffer* GetBuffer(int _index) const;
    //Buffer* GetBuffer(int _index);
    void draw();



};

