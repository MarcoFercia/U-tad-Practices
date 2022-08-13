
#include <vector>

class Buffer;
class Shader;
class Material;


class Mesh
{
public:

    Mesh();
    ~Mesh();


private:

    std::vector<Buffer*> bufferVector;
    std::vector<Material*> materialsVector;

public:

    static Mesh* load(const char* _filename, const Shader* _shader = nullptr);

    void addBuffer(Buffer* _buffer,Material* _material);
    size_t getNumBuffers() const;
    const Buffer* GetBuffer(int _index) const;

    size_t getNumMaterials() const;
    const Material* getMaerial(size_t _index) const;

    void draw();



};

