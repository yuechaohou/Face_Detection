#!/usr/bin/env sh
DATA=/home/capstone/adaboost/adaboost_test
MY=/home/capstone/cnn_train_models/train_2class
negative=0
positve=1

echo "Create train.txt..."
rm -rf $MY/train3.txt
for i in image001 image002 image003 image004 image005 image007 image009 image011 image012 image015 image016 image017 image018 image019 image021 image023 image024 image026 image027 image028 image029 image030 image032 image033 image034 image035 image037 image038 image039 image040 image042 image043 image045 image046 image047 image048 image049 image050 image052 image053 image054 image056 image060 image061 image064 image065 image066 image067 image068 image069 image070 image071 image072 image073 image074 image075 image076 image077 image078 image079 image081 image082 image084 image085 image086 image087 image089 image090 image092 image093 image094 image095 image096 image097 image098 image100 image101 image102 image103 image104 image105 image107 image108 image109 image111 image112 image113 image115 image116 image117 image118 image120 image121 image123 image124 image126 image128 image129 image130 image131 image132 image133 image134 image135 image136 image137 image138 image139 image140 image142 image143 image144 image147 image149 image151 image152 image153 image154 image158 image159 image161 image163 image164 image165 image166 image167 image168 image170 image171 image172 image173 image174 image176 image177 image179 image180 image181 image183 image184 image185 image186 image187 image188 image190 image191 image192 image193 image194 image195 image197 image198 image199 image200 image201 image202 image204 image207 image209 image210 image211 image212 image214 image215 image217 image218 image219 image220 image221 image222 image223 image224 image225 image226 image228 image229 image230 image231 image232 image233 image235 image236 image237 image238 image239 image240 image241 image243 image244 image245 image246 image247 image248 image249 image251 image252 image253 image254 image255 image256 image257 image260 image261 image263 image265 image266 image269 image270 image271 image272 image273 image274 image275 image276 image278 image279 image280 image281 image283 image285 image286 image287 image288 image290 image292 image293 image294 image295 image297 image298 image299 image302 image303 image305 image306 image307 image308 image309 image310 image311 image313 image314 image316 image317 image319 image321 image322 image324 image325 image326 image327 image328 image329 image331 image333 image334 image336 image338 image339 image340 image341 image342 image343 image344 image345 image346 image347 image349 image350 image351 image352 image353 image354 image355 image356 image358 image360 image361 image362 image363 image364 image365 image366 image367 image368 image371 image374 image375 image376 image377 image379 image380 image383 image384 image385 image386 image387 image390 image391 image392 image393 image394 image395 image396 image397 image398 image399 image400 image401 image402 image403 image404 image405 image408 image409 image410 image411 image412 image414 image416 image417 image419 image420 image422 image423 image424 image425 image426 image428 image430 image431 image432 image433 image434 image438 image439 image440 image441 image443 image445 image447 image451 image452 image453 image454 image455 image456 image458 image459 image460 image461 image462 image463 image464 image465 image466 image467 image468 image469 image470 image472 image473 image474 image475 image476 image477 image478 image479 image480 image481 image482 image483 image484 image487 image488 image489 image490 image491 image492 image496 image497 image498 image499 image500 image501 image502 image505 image506 image508 image509 image510 image511 image513 image514 image516 image517 image518 image521 image524 image525 image526 image527 image528 image529 image530 image533 image534 image535 image536 image537 image538 image539 image540 image542 image543 image544 image545 image548 image550 image551 image553 image555 image557 image558 image559 image560 image561 image562 image563 image565 image566 image567 image568 image570 image571 image572 image573 image574 image575 image577 image578 image579 image580 image581 image582 image583 image587 image588 image589 image590 image591 image593 image595 image596 image597 image598 image601 image602 image604 image605 image606 image608 image610 image611 image612 image613 image614 image615 image616 image619 image622 image623 image624 image627 image629 image630 image631 image632 image635 image637 image638 image642 image643 image645 image646 image649 image651 image652 image653 image654 image655 image656 image657 image661 image666 image667 image669 image670 image671 image673 image675 image678 image680 image682 image684 image685 image686 image687 image688 image689 image691 image692 image693 image694 image696 image697 image698 image699 image701 image702 image703 image704 image705 image706 image707 image708 image710 image712 image713 
do
find $DATA/new_negative -name $i*.jpg | cut -d '/' -f 1-9 | sed "s/$/ 0/">>$MY/train3.txt
find $DATA/new_positive -name $i*.jpg | cut -d '/' -f 1-9 | sed "s/$/ 1/">>$MY/train3.txt
done
echo "All done"