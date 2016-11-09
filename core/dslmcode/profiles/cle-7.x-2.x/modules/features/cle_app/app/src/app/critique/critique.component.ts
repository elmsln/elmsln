import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Params } from '@angular/router';
import { Location } from '@angular/common';

@Component({
  selector: 'cle-critique',
  templateUrl: './critique.component.html',
  styleUrls: ['./critique.component.css']
})
export class CritiqueComponent implements OnInit {
  submissionId: number;

  constructor(
    private route: ActivatedRoute,
    private location: Location
  ) { }

  ngOnInit() {
    this.route.params.forEach((params: Params) => {
      let id = +params['id'];
      this.submissionId = id;
    });
  }
}
