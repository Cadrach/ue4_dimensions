'use strict';

/* App Module */

var dimensionsControllers = angular.module('dimensionsControllers', []);

dimensionsControllers.controller('MainCtrl', ['$scope',
    function($scope) {
        $scope.testValue = "WORKING";

        var cy = cytoscape({
            container: document.getElementById('network'),

            boxSelectionEnabled: false,
            autounselectify: true,

            style: cytoscape.stylesheet()
                .selector('node')
                .css({
                    // 'content': 'data(id)'
                    'background-color': '#000',
                    'height': 30,
                    'width': 30,
                    'shadow-blur': 30,
                    'shadow-opacity': .75,
                    'shadow-color': '#FF0000',
                    'shadow-offset-x': 0,
                    'shadow-offset-y': 0,
                })
                .selector('edge')
                .css({
                    'curve-style': 'unbundled-bezier',
                    'control-point-distances': '0 0',
                    'control-point-weights': '0.25 0.75',

                    'transition-property': 'control-point-distances',
                    'transition-duration': '5s',
//                    'transition-timing-function': 'ease-out-quad',

                    'target-arrow-color': '#000',
                    'target-arrow-shape': 'none',

                    'width': 5,
                    'line-color': '#000',

                    'shadow-blur': 20,
                    'shadow-opacity': .75,
                    'shadow-color': '#FF0000',
                    'shadow-offset-x': 1,
                    'shadow-offset-y': 0,
                })
                .selector('.flow')
                .css({
                     // 'background-color': '#61bffc',
                     // 'line-color': '#61bffc',
                     // 'target-arrow-color': '#61bffc',
                     'control-point-distances': '30 -30',
                })
                .selector('.flowBack')
                .css({
                     // 'background-color': '#61bffc',
                     // 'line-color': '#61bffc',
                     // 'target-arrow-color': '#61bffc',
                     'control-point-distances': '-30 30',
                }),

            elements: {
                nodes: [
                    {data: {id : 0, label : 0, level : 0, option_level: 'Hangar'}},
                    {data: {id : 1, label : 1, level : 1}},
                    {data: {id : 2, label : 2, level : 3}},
                    {data: {id : 3, label : 3, level : 4}},
                    {data: {id : 4, label : 4, level : 4}},
                    {data: {id : 5, label : 5, level : 5}},
                    {data: {id : 6, label : 6, level : 1}},
                    {data: {id : 7, label : 7, level : 2}},
                    {data: {id : 8, label : 8, level : 4}},
                    {data: {id : 9, label : 9, level : 4}},
                    {data: {id : 10, label : 10, level : 2}},
                    {data: {id : 11, label : 11, level : 1}},
                    {data: {id : 12, label : 12, level : 2}},
                    {data: {id : 13, label : 13, level : 1}},
                    {data: {id : 14, label : 14, level : 5}},
                ],

                edges: [
                    {data: {weight: 1, source: 0, target: 1}},
                    {data: {weight: 2, source: 0, target: 6}},
                    {data: {weight: 3, source: 0, target: 13}},
                    {data: {weight: 4, source: 0, target: 11}},
                    {data: {weight: 5, source: 1, target: 2}},
                    {data: {weight: 6, source: 2, target: 3}},
                    {data: {weight: 7, source: 2, target: 4}},
                    {data: {weight: 8, source: 3, target: 5}},
                    {data: {weight: 9, source: 1, target: 10}},
                    {data: {weight: 10, source: 1, target: 7}},
                    {data: {weight: 11, source: 2, target: 8}},
                    {data: {weight: 12, source: 2, target: 9}},
                    {data: {weight: 13, source: 3, target: 14}},
                    {data: {weight: 14, source: 1, target: 12}},
                    {data: {weight: 15, source: 13, target: 12}}
                ]
            },

            layout: {
                name: 'dagre',
                nodeSep: 10, // the separation between adjacent nodes in the same rank
                edgeSep: -10, // the separation between adjacent edges in the same rank
                rankSep: undefined, // the separation between adjacent nodes in the same rank
                rankDir: 'BT', // 'TB' for top to bottom flow, 'LR' for left to right
                minLen: function( edge ){ return 1; }, // number of ranks to keep between the source and target of the edge
                edgeWeight: function( edge ){ return 1; }, // higher weight edges are generally made shorter and straighter than lower weight edges
                // roots: '#0',
                // padding: 10
            }
        });

        var pathes = cy.elements().bfs('#0', function(){}, true).path;

        // function flow(){
        //     pathes.animate({
        //         style: {'control-point-distances': '30 -30',},
        //         position: { x: 100, y: 100 },
        //         // 'transition-property': 'control-point-distances',
        //         // 'transition-duration': '5s',
        //         // 'transition-timing-function': 'ease-out-quad',
        //     }, {duration: 5000})
        // }
        //
        // flow();
        console.log(cy.edges());
        $scope.flow = function (cycle){
            var value = Math.random()*20 + 10;
            var cycles = [
                value + ' 0',
                '-' + value +' 0'
            ];
            var blur = [
                10,
                30,
                10,
                30
            ];
            var duration = (Math.random()*4+1) *1000;
            cy.edges().animate({
                style: { 'control-point-distances': cycles[cycle]},
                // style: { 'control-point-weights': value ? '0 1':'1 0'},
                queue: true,
                // easing: 'ease',
                duration: duration
            });
            setTimeout(function(){$scope.flow((cycle+1)%cycles.length)}, duration)
        }

        $scope.flow(0);
//
//        $scope.flowCss = function(){
//            cy.edges().css({
//                'control-point-distances': '30 -30',
//                'transition-property': 'control-point-distances',
//                'transition-duration': '5s',
//                'transition-timing-function': 'ease-out-quad',
//            })
//        }

//        setTimeout($scope.flowCss, 1000);

//        cy.edges().classes('flow');
//        setTimeout(function(){
//            cy.edges().removeClass('flow').classes('flowBack');
//        }, 5000)
    }]);