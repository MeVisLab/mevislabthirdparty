#!/usr/bin/env bash
set -e

#
# small script to fetch and prepare the Qt5 Patch Collection
#
# Qt 5 Patch Collection is the patch-set KDE maintaince to provide
# security fixes, crash fixes, and other functional defects atop the
# Qt5 code-base, in particular Qt 5.15 LTS.
#
# This collection generally only contains patches if they have been
# merged upstream first.
#
# see: https://community.kde.org/Qt5PatchCollection
#

export QTVERSION="5.15.7"

# the directory of the script
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# the temp directory used, within $DIR
WORKDIR=`mktemp -d`

if [[ ! "$WORKDIR" || ! -d "$WORKDIR" ]]; then
  echo "Could not create temp dir"
  exit 1
fi
export WORKDIR

echo "=== ${WORKDIR}"

function cleanup {
  rm -rf "$WORKDIR"
  echo "Deleted temp working directory $WORKDIR"
}
trap cleanup EXIT

echo "=== ${WORKDIR} ==="

git -C ${WORKDIR} clone https://invent.kde.org/qt/qt/qt5.git -b v${QTVERSION}-lts-lgpl kde-qt5
git -C ${WORKDIR}/kde-qt5 submodule init
git -C ${WORKDIR}/kde-qt5 submodule update
git -C ${WORKDIR}/kde-qt5 submodule foreach --recursive 'if git rev-parse --verify v${QTVERSION}-lts-lgpl; then if git rev-parse --verify origin/kde/5.15; then git format-patch --keep-subject --no-stat v${QTVERSION}-lts-lgpl..origin/kde/5.15 -o ${WORKDIR}/patches/${path};fi;fi'

mkdir ${WORKDIR}/qt5
wget -c https://download.qt.io/archive/qt/5.15/${QTVERSION}/single/qt-everywhere-opensource-src-${QTVERSION}.tar.xz -O ${WORKDIR}/qt-everywhere-opensource-src-${QTVERSION}.tar.xz
tar -xvf ${WORKDIR}/qt-everywhere-opensource-src-${QTVERSION}.tar.xz --strip-components=1 -C ${WORKDIR}/qt5
rm ${WORKDIR}/qt-everywhere-opensource-src-${QTVERSION}.tar.xz

git -C ${WORKDIR}/qt5 init
git -C ${WORKDIR}/qt5 config gc.auto 0
git -C ${WORKDIR}/qt5 add --all
git -C ${WORKDIR}/qt5 commit -m "inital"

rm -rf ${DIR}/patches/upstream
mkdir -p ${DIR}/patches/upstream/failed

pushd ${DIR} >/dev/null
for i in `find ${WORKDIR}/patches -type f`; do
    fn=$(basename $i)
    dn=$(basename $(dirname $i))

    if git -C ${WORKDIR}/qt5 apply --ignore-whitespace --directory "$dn" --check "$i"; then
        git -C ${WORKDIR}/qt5 am --ignore-whitespace --directory "$dn" < "$i"
        git -C ${WORKDIR}/qt5 show --src-prefix='i/' --dst-prefix='w/' > "${DIR}/patches/upstream/${QTVERSION}-${dn}_${fn:5}"
    else
        >&2 echo "Failed to apply patch: $i"
        mv "$i" "${DIR}/patches/upstream/failed/"
    fi
done
popd >/dev/null

pushd ${DIR} >/dev/null
echo "" > patches.yml
for i in `find patches/upstream -type f`; do
    echo "    - patch_file: ${i}"                             >> patches.yml
    #echo "      base_path: sources/$(basename $(dirname $i))" >> patches.yml
    #echo "      strip: '0'"                                   >> patches.yml
done
popd >/dev/null

echo
echo "DONE"
echo
