pkgname="gnuplot-gtk"
pkgver="5.4.2"
pkgrel="1"
pkgdesc="Plotting package which outputs to GTK4"
arch=("x86_64")
url="http://www.gnuplot.info"
depends=("readline" "cairo" "gtk4")

build()
{
    cd "${srcdir}"
    make
}

package()
{
    cd "${srcdir}"
    make DESTDIR="${pkgdir}" install
}
