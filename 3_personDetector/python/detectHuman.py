import numpy as np
import cv2


def inside(r, q):
    rx, ry, rw, rh = r
    qx, qy, qw, qh = q
    return rx > qx and ry > qy and rx + rw < qx + qw and ry + rh < qy + qh


def draw_detections(img, rects, thickness = 1):
    for x, y, w, h in rects:
        # the HOG detector returns slightly larger rectangles than the real objects.
        # so we slightly shrink the rectangles to get a nicer output.
        pad_w, pad_h = int(w), int(h)
        cv2.rectangle(img, (x+pad_w, y+pad_h), (x+w-pad_w, y+h-pad_h), (0, 255, 0), thickness)


if __name__ == '__main__':
    import sys
    from glob import glob
    import itertools as it
    from Background_Subtraction import sendImg

    print(__doc__)

    hog = cv2.HOGDescriptor()
    hog.setSVMDetector( cv2.HOGDescriptor_getDefaultPeopleDetector() )
    img3=sendImg()
	#replace the image source
    default = ['/home/gunner/Desktop/cultural8.jpg'] if len(sys.argv[1:]) == 0 else []

    for fn in it.chain(*map(glob, default + sys.argv[1:])):
        print(fn, ' - ',)
        try:
            img = cv2.imread(fn)
            if img is None:
                print('Failed to load image file:', fn)
                continue
        except:
            print('loading error')
            continue

        found, w = hog.detectMultiScale(img, winStride=(8,8), padding=(32,32), scale=1.05)
        found_filtered = []
        for ri, r in enumerate(found):
            for qi, q in enumerate(found):
                if ri != qi and inside(r, q):
                    break
            else:
                found_filtered.append(r)
        #draw_detections(img, found)
        #draw_detections(img, found_filtered, 3)
        draw_detections(img3,found)
        draw_detections(img3, found_filtered, 3)
        print('%d (%d) found' % (len(found_filtered), len(found)))
        cv2.imshow('img', img)
        ch = cv2.waitKey()
        if ch == 27:
            break
cv2.destroyAllWindows()