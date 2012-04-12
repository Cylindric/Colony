class Map { };
 
class SceneManager
{
public:
        void Initialise() { mMap = new Map; }
 
private:
        Map* mMap;
};
 
int main() {
  SceneManager sm;
  sm.Initialise();
}
 