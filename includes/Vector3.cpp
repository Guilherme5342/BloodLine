#include "Vector3.h"

/// <summary>
/// Console Prints para Vector3
/// </summary>
/// <param name="out"></param>
/// <param name="vec"></param>
/// <returns></returns>
ostream& operator<<(ostream& out, const Vector3& vec)
{
    // ToDO: inserir instrução return aqui

    out << "( " << vec.x << " , " << vec.y << " , " << vec.z << " )";
    return out;
}

/// <summary>
/// Console Print para Vector2
/// </summary>
/// <param name="out"></param>
/// <param name="vec"></param>
/// <returns></returns>
ostream& operator<<(ostream& out, const Vector2& vec)
{
    // TODO: inserir instrução return aqui

    out << "(" << vec.x << "," << vec.y << ")";
    return out;
}
