'use strict';

/* App Module */

var dimensionsControllers = angular.module('dimensionsControllers', []);

dimensionsControllers.controller('MainCtrl', ['$scope',
    function($scope) {
        $scope.testValue = "WORKING";


        // create a network
        var container = document.getElementById('network');
        var data = {
            "nodes" : [{
                "id" : 0,
                "label" : "0",
                "level" : 0,
                "option_level": 'Hangar',
            }, {
                "id" : 1,
                "label" : "1",
                "level" : 1
            }, {
                "id" : 2,
                "label" : "2",
                "level" : 3
            }, {
                "id" : 3,
                "label" : "3",
                "level" : 4
            }, {
                "id" : 4,
                "label" : "4",
                "level" : 4
            }, {
                "id" : 5,
                "label" : "5",
                "level" : 5
            }, {
                "id" : 6,
                "label" : "6",
                "level" : 1
            }, {
                "id" : 7,
                "label" : "7",
                "level" : 2
            }, {
                "id" : 8,
                "label" : "8",
                "level" : 4
            }, {
                "id" : 9,
                "label" : "9",
                "level" : 4
            }, {
                "id" : 10,
                "label" : "10",
                "level" : 2
            }, {
                "id" : 11,
                "label" : "11",
                "level" : 1
            }, {
                "id" : 12,
                "label" : "12",
                "level" : 2
            }, {
                "id" : 13,
                "label" : "13",
                "level" : 1
            }, {
                "id" : 14,
                "label" : "14",
                "level" : 5
            }
            ],
            "edges" : [{
                id: 1,
                "from" : 0,
                "to" : 1,
                width: 20
            }, {
                id: 2,
                "from" : 0,
                "to" : 6
            }, {
                id: 3,
                "from" : 0,
                "to" : 13
            }, {
                "from" : 0,
                "to" : 11
            }, {
                "from" : 1,
                "to" : 2
            }, {
                "from" : 2,
                "to" : 3
            }, {
                "from" : 2,
                "to" : 4
            }, {
                "from" : 3,
                "to" : 5
            }, {
                "from" : 1,
                "to" : 10
            }, {
                "from" : 1,
                "to" : 7
            }, {
                "from" : 2,
                "to" : 8
            }, {
                "from" : 2,
                "to" : 9
            }, {
                "from" : 3,
                "to" : 14
            }, {
                "from" : 1,
                "to" : 12
            }, {
                "from" : 13,
                "to" : 12
            }
            ]
        }


        var options = {
            nodes:{
                borderWidth: 5,
                fixed: true,
//                font: {size: 40},
                shape: 'circle',
                image: 'img/giphy.gif'
            },
            edges: {
                smooth: {
                    type: 'cubicBezier',
                    forceDirection: 'vertical',
                    roundness: 0.5
                },
                width: 15,
                color: '#000',
                shadow: {
                    enabled: true,
                    x: 0,
                    y: 0,
                    size: 15,
                    color: 'rgba(255,0,0,0.5)'
                } //can be object
            },
            layout: {
                hierarchical: {
                    direction: 'DU'
                }
            },
            physics:false
        };

        //Create image for each nodes
        _.each(data.nodes, function(node){
            node.html = jQuery('<div class="node animated infinite pulse"></div>');
            node.html.css({
                'animation-delay': (Math.random()*2+0.5) + 's' //between 0.5 & 2
            })
            node.html.click(function(){
                // console.log("nodeSelected", node.id)
                // document.write('Node Selected:' + node.id)
                if(window.blu_event){
                    blu_event("nodeSelected", node.id+'');
                }
            })
            angular.element('body').append(node.html);
        })

        var network = new vis.Network(container, data, options);

        //
        // network.moveTo({
        //     position: network.getPositions([9])[9],    // position to animate to (Numbers)
        //     scale: 1.5,              // scale to animate to  (Number)
        //     //offset: {x:x, y:y},      // offset from the center in DOM pixels (Numbers)
        //     animation: {             // animation object, can also be Boolean
        //         duration: 1000,                 // animation duration in milliseconds (Number)
        //         easingFunction: "easeInOutQuad" // Animation easing function, available are:
        //     }                                   // linear, easeInQuad, easeOutQuad, easeInOutQuad,
        // });

        // network.on('click', function(data){
        //     //blu_event("nodeSelected", data.nodes[0]);
        //     if(window.blu_event){
        //         blu_event('VIS Clicked', ": X=" + data.event.center.x + ', Y=' + data.event.center.y);
        //     }
        //     else{
        //         console.log(data.event.center)
        //     }
        //
        // })

        network.on('afterDrawing', function(){
//            console.log(network.getPositions());
            _.each(network.getPositions(), function(position, nodeId){
                var domPosition = network.canvasToDOM(position);
                data.nodes[nodeId].html.css({
                    left: domPosition.x,
                    top: domPosition.y,
                    position: 'absolute'
                });
                // data.nodes[nodeId].html.html(Math.round(domPosition.x) + ',' + Math.round(domPosition.y) + '<br/>' + nodeId)
            })

            // network.redraw()
            // console.log(network.canvas.frame.canvas.getContext("2d"));
        })

        jQuery(document).click(function(event){
            $scope.debug = event;
        })

        $scope.debug = jQuery(window).width() + 'x' + jQuery(window).height();
    }]);