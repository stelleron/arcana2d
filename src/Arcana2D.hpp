#ifndef ARCANA2D_LIBRARY
    #define ARCANA2D_LIBRARY
    
    // Includes
    #include <string>
    #include <glm/glm.hpp>
    #include <glad/glad.h>

    // Exposed library functions and classes
    namespace arcana {
        // ====== COLOR.HPP ======
        // Used to create a color object
        struct Color {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;

            // Constructor options
            Color();
            Color(unsigned char r, unsigned char g, unsigned char b);
            Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

            // Static constructors
            static Color RGB(unsigned char r, unsigned char g, unsigned char b);
            static Color RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
            static Color HSV(float h, float s, float v);
            static Color HSVA(float h, float s, float v, unsigned char a);
            static Color NormalRGB(float r_normal, float g_normal, float b_normal);
            static Color NormalRGBA(float r_normal, float g_normal, float b_normal, float a_normal);
            static Color HexRGB(int hexValue);
            static Color HexRGBA(int hexValue);
        };

        // COLOR MACROS
        #define WHITE arcana::Color::RGB(255, 255, 255)
        #define RED arcana::Color::RGB(255, 0, 0)
        #define GREEN arcana::Color::RGB(0, 255, 0)
        #define YELLOW arcana::Color::RGB(255, 255, 0)
        #define BLUE arcana::Color::RGB(0, 0, 255)
    

        // ====== VECTOR.HPP ======
        // Namespace defines
        // Used to define vectors
        using Vector2 = glm::vec2;
        using Vector3 = glm::vec3;
        using Vector4 = glm::vec4;

        // Used to define matrices
        using Mat2 = glm::mat2;
        using Mat3 = glm::mat3;
        using Mat4 = glm::mat4;

        // ====== VERTEX.HPP ======
        // Used to create a vertex object
        // Used to create a vertex object
        struct Vertex {
            Vector2 pos;
            Vector2 texCoords;
            Color color;

            // Constructor
            Vertex();
            Vertex(Vector2 pos);
            Vertex(Vector2 pos, Color color);
            Vertex(Vector2 pos, Color color, Vector2 texCoords);
        };

        // ====== CAMERA.HPP ======
        // Used to create a 2D camera
        class Camera {
            private:
                Vector2 camera_dim; // Stores the camera dimensions
            public:
                // Constructor
                Camera();
                // Destructor 
                ~Camera();

                // Configure the camera to default settings
                void defaultSettings(int width, int height);

                // Get the projection matrix
                Mat4 getProjectionMatrix();
        };

        // ====== GEOMETRY.HPP ======
        // Used to create a line object
        struct Line {
            Vector2 startPoint;
            Vector2 endPoint;
            
            // Constructors
            Line();
            Line(Vector2 startPoint, Vector2 endPoint);
        };

        // Used to create a triangle
        struct Triangle {
            Vector2 point1;
            Vector2 point2;
            Vector2 point3;

            // Constructors
            Triangle();
            Triangle(Vector2 point, int width, int height); // Right angle triangle
            Triangle(Vector2 point1, Vector2 point2, Vector2 point3);
        };

        // Used to create a quadrilateral
        struct Quadrilateral {
            Vector2 point1;
            Vector2 point2;
            Vector2 point3;
            Vector2 point4;

            // Constructors
            Quadrilateral();
            Quadrilateral(Vector2 point1, Vector2 point2, Vector2 point3, Vector2 point4);
        };   

        // Used to create a rectangle
        struct Rectangle {
            Vector2 point;
            int width;
            int height;

            // Constructors
            Rectangle();
            Rectangle(Vector2 point, int size); // Square
            Rectangle(Vector2 point, int width, int height);
        };

        // Used to create a circle
        struct Circle {
            Vector2 center;
            int radius;

            // Constructors
            Circle();
            Circle(Vector2 center, int radius);
        };

        // ====== DRAWGEOMETRY.HPP ======

        // Used to create a triangle with color
        struct DrawTriangle : public Triangle {
            Color color;
            DrawTriangle(const Triangle& triangle, const Color& color);
        };

        // Used to make drawable objects
        DrawTriangle makeDrawable(const Triangle triangle, const Color color);
        
        // ====== VERTEXBUFFER.HPP ======
         // Enum for draw modes
        enum RenderMode {
            Points,
            Lines,
            Triangles,
            Quads,
            Circle
        };

        // Used to create a buffer to track elements 
        struct ElementBuffer {
            unsigned int* iArray;
            size_t totalSize;

            // Constructor
            ElementBuffer(RenderMode rMode, int size);
            // Destructor 
            ~ElementBuffer();

            // Setters/getters
            size_t getSize();
        };
        
        // Used to create a vertex array buffer with a fixed size
        struct VertexBuffer {
            private:
                ElementBuffer* eBuffer; // Pointer to element buffer
                Vertex* vArray; // List of vertices
                int vSize; // Number of vertices
                int primSize; // The size of the primitive
                RenderMode rMode; // Render mode
            public:
                // Constructor
                VertexBuffer(RenderMode rMode, int primNum);
                // Destructor
                ~VertexBuffer();

                // Check if there is space to add an object, returns True if available
                bool checkSpace(int startIndex, int numVertices);

                // Clear the vertex buffer
                void clear();

                // Convert the vertex array into a float array (heap allocated)
                float* getFloatArray();
                // Get the size of the array
                size_t getArraySize();
                // Get the render type of the buffer 
                inline RenderMode getRenderType() {return rMode;}
                // Get the index array
                unsigned int* getIndexArray();
                // Get the size of the index array
                size_t getIndexArraySize();
                // Set an induvidual vertex with the array operator
                Vertex& operator[](int index);
                // Get an induvidual vertex with the array operator
                Vertex operator[](int index) const;

                // Used to add objects to the vertex buffer 
                void add(const Triangle& triangle, int startIndex);
                void add(const DrawTriangle& triangle, int startIndex);

                void add(const Rectangle& rectangle, int startIndex);
        };

        // ====== IMAGE.HPP ======
        // Namespace for loading images
        struct Image {
            unsigned char* data;
            int width;
            int height;
            int colorChannels;

            // Constructor
            Image();
            Image(const char* path);
            // Destructor 
            ~Image();

            void load(const char* path);
        };

        // ====== SHADER.HPP ======
        // Used to create a shader class 
        class Shader {
            private:
                bool is_init;
                unsigned int id;
            public:
                // Different shader constructors 
                Shader();
                Shader(int exclude1, int exclude2);
                Shader(const char* vSource, int exclude);
                Shader(int exclude, const char* fSource);
                Shader(const char* vSource, const char* fSource);

                // Uniform setting functions
                void setBool(const char* name, bool value);  
                void setInt(const char* name, int value);   
                void setFloat(const char* name, float value);
                void setMat4(const char* name, Mat4 matrix);

                // Use the shader
                void use();

                // Getters
                inline const unsigned int getID() {return id;}
                inline const bool getInit() {return is_init;}

                // Setters
                void deInit() { is_init = false;}

                // Copy assignment operator
                Shader& operator=(Shader& shader) {
                    if (is_init) {glDeleteProgram(id);} 
                    id = shader.getID();
                    shader.deInit();
                    is_init = true;
                    return *this;
                }

                // Destructor
                ~Shader();
        };
        
        // ====== SPRITE.HPP ======
        // Used to create a sprite
        class Sprite {
            private:
                unsigned int id; 
                bool is_init;

            public:
                // Properties
                Vector2 pos; 
                int width;
                int height;

                // Constructor
                Sprite();
                Sprite(const char* path);

                // Load the sprite
                void load(const char* path);
                // Get the ID of the sprite
                inline unsigned int getID() {return id;}

                // Destructor
                ~Sprite();
        };

        // ====== RENDERCONTEXT.HPP ======
        // Used to create a render context to draw objects
        class RenderContext {
            private:
                Shader* curr_shader; // Stores the current shader
                Camera* curr_camera; // Stores the current camera
                unsigned int defaultTextureID; // Stores a default texture

                void setVertexAttributes();
            public:
                // Constructor
                RenderContext();
                // Destructor
                ~RenderContext();
                
                // Used to initialise the renderer
                void init();
                // Use the shader after setting some uniforms
                void useShader();
                // Set the current camera
                void setCurrentCamera(Camera* camera);
                 // Set the current shader
                void setCurrentShader(Shader* shader);

                // Draw functions
                void draw(VertexBuffer& buffer);
                void draw(Sprite& sprite);
        };

        // ====== AUDIO.HPP ======
        // Used to create the audio context
        class AudioContext {
            public:
                // Constructor
                AudioContext();
                // Destructor
                ~AudioContext();

                // Play a sound
                void playSound(const char* soundpath);
        };

        // ====== APPCONFIG.HPP ======
        // Used to configure the application
        struct AppConfig {
            int width;
            int height;
            std::string title;
            Color background_color;

            bool resizable; 
            bool maximized; 
            bool fullscreen;
            bool vsync;
            bool transparent;
            bool focused;
            bool haltWhileHidden; // Set whether the app will pause while hidden

            // Default constructor
            AppConfig();
        };

        // ====== GAMECONTEXT.HPP ======
        // Used to communicate with the application logic
        class GameContext {
            private:
                Camera* curr_camera;
            public:
                // Constructor
                GameContext();
                // Destructor
                ~GameContext();

                // SETTERS
                // =======
                void setCamera(Camera& camera);

                // GETTERS
                // =======
                Camera* getCamera();
        };

        // ====== APPLICATION.HPP ======
        // Used to create the Application class to be extended
        class Application {
            // Application virtual functions
            public:
                virtual void config(AppConfig& config) = 0;
                virtual void init() = 0;
                virtual void update(GameContext& ctx) = 0;
                virtual void render(RenderContext& ctx) = 0;
                virtual void finish() = 0;
        };

        // Used to create the application
        void build(Application& app);
    }
#endif